package BLOCK

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"strconv"
	"strings"
	"time"
)

//区块结构体
type Block struct {
	Diff      int
	Index     int
	Nonce     int
	PreHash   string
	Hashcode  string
	TimeStamp string
	Value     string
}

//生成每一个区块的哈希值
func GenerationHashValue(block Block) string {
	var hashdata = strconv.Itoa(block.Index) + strconv.Itoa(block.Nonce) + strconv.Itoa(block.Diff) + block.TimeStamp
	var hashmy = sha256.New()
	hashmy.Write([]byte(hashdata))
	hashed := hashmy.Sum(nil)
	return hex.EncodeToString(hashed)
}

//初始区块声明
func GenerateFirstBlock(data string) Block {
	var chuangshi Block
	chuangshi.PreHash = "0"
	chuangshi.TimeStamp = time.Now().String()
	chuangshi.Diff = 3
	chuangshi.Value = data
	chuangshi.Index = 1
	chuangshi.Nonce = 0
	chuangshi.Hashcode = GenerationHashValue(chuangshi)
	return chuangshi
}

//生成之后的区块
func GenerateNextBlock(data string, oldBlock Block) Block {
	var newBlock Block
	newBlock.TimeStamp = time.Now().String()
	newBlock.Diff = 3
	newBlock.Index = oldBlock.Nonce + 1
	newBlock.Value = data
	newBlock.PreHash = oldBlock.Hashcode
	newBlock.Nonce = 0
	newBlock.Hashcode = pow(newBlock.Diff, &newBlock)
	fmt.Println("挖到了一个区块")
	return newBlock
}

//pow工作量证明
func pow(diff int, block *Block) string {
	for {
		hashmy := GenerationHashValue(*block)
		if strings.HasPrefix(hashmy, strings.Repeat("0", diff)) {
			return hashmy
		} else {
			block.Nonce++
		}
	}
}
