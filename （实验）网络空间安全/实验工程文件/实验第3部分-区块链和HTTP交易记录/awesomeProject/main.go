package main

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"github.com/davecgh/go-spew/spew"
	"github.com/gorilla/mux"
	"github.com/joho/godotenv"
	"io"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"
)

const differculty = 3

type Block struct {
	Index     int
	Timestamp string
	BMP       int
	HashCode  string
	PreHash   string
	Diff      int
	Nonce     int
}

var Blockchain []Block

var mutex = &sync.Mutex{}

func generateBlock(oldBlock Block, BMP int) Block {
	var newBlock Block
	newBlock.PreHash = oldBlock.HashCode
	newBlock.Timestamp = time.Now().String()
	newBlock.Index = oldBlock.Index + 1
	newBlock.BMP = BMP
	newBlock.Diff = differculty

	//
	for i := 0; ; i++ {
		newBlock.Nonce++
		hash := calculationHash(newBlock)
		fmt.Println(hash)
		if ishashvalid(hash, newBlock.Diff) {
			fmt.Println("成功")
			newBlock.HashCode = hash
			return newBlock
		}
	}
}

func calculationHash(block Block) string {
	record := strconv.Itoa(block.Index) + block.PreHash + strconv.Itoa(block.Nonce) + strconv.Itoa(block.BMP) + block.PreHash
	sha := sha256.New()
	sha.Write([]byte(record))
	hashed := sha.Sum(nil)
	return hex.EncodeToString(hashed)
}

func ishashvalid(hash string, difficulty int) bool {
	prefix := strings.Repeat("0", difficulty)
	return strings.HasPrefix(hash, prefix)

}

func main() {
	err := godotenv.Load()
	if err != nil {
		log.Fatal(err)
	}
	go func() {
		genesisblock := Block{}
		genesisblock = Block{
			0, time.Now().String(), 0, calculationHash(genesisblock),
			"", differculty, 0}
		mutex.Lock()
		Blockchain = append(Blockchain, genesisblock)
		mutex.Unlock()
		spew.Dump(genesisblock)
	}()
	log.Fatal(run())
}

//http启动
func run() error {
	mux := makeMuxRouter()
	httpAddr := os.Getenv("ADDR")
	log.Println("listening on", os.Getenv("ADDR"))
	s := &http.Server{
		Addr:           ":" + httpAddr,
		Handler:        mux,
		ReadTimeout:    10 * time.Second,
		WriteTimeout:   10 * time.Second,
		MaxHeaderBytes: 1 << 20,
	}
	if err := s.ListenAndServe(); err != nil {
		return err
	}
	return nil
}

func makeMuxRouter() http.Handler {
	muxRouter := mux.NewRouter()
	muxRouter.HandleFunc("/", handgetblockhain).Methods("GET")
	muxRouter.HandleFunc("/", handerwriteblock).Methods("POST")
	return muxRouter
}

func handgetblockhain(w http.ResponseWriter, r *http.Request) {
	bytes, err := json.MarshalIndent(Blockchain, "", "\t")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	io.WriteString(w, string(bytes))
}

//声明一个post类型的数据类型
type Message struct {
	BPM int
}

func handerwriteblock(writer http.ResponseWriter, request *http.Request) {
	writer.Header().Set("Content-Type", "application/json")
	var message Message
	decoder := json.NewDecoder(request.Body)
	if err := decoder.Decode(&message); err != nil {
		respondWithJson(writer, request, http.StatusNotFound, request.Body)
		return
	}
	defer request.Body.Close()

	//生成区块
	mutex.Lock()
	newblock := generateBlock(Blockchain[len(Blockchain)-1], message.BPM)
	mutex.Unlock()

	//判断是否合法
	if isblockivaild(newblock, Blockchain[len(Blockchain)-1]) {
		Blockchain = append(Blockchain, newblock)
		spew.Dump(Blockchain)
	}
	respondWithJson(writer, request, http.StatusCreated, newblock)
}

func respondWithJson(writer http.ResponseWriter, request *http.Request, code int, inter interface{}) {
	writer.Header().Set("Content-Type", "application/json")
	//格式化输出JSON
	response, err := json.MarshalIndent(inter, "", "\t")
	if err != nil {
		writer.WriteHeader(http.StatusInternalServerError)
		writer.Write([]byte("HTTP 500:Serve Error"))
		return
	}
	writer.WriteHeader(code)
	writer.Write(response)
}

func isblockivaild(newBlock, oldblock Block) bool {
	if oldblock.Index+1 != newBlock.Index {
		return false
	}
	if oldblock.HashCode != newBlock.PreHash {
		return false
	}
	if calculationHash(newBlock) != newBlock.HashCode {
		return false
	}
	return true
}
