<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h33pbiaq8kj20n4074my3.jpg" alt="image-20220611021758986" style="zoom:33%;" />

# 基于共识算法和区块链模拟实现超级账本

实验语言：GO

实验环境：GoLand 2022.1 ； go 1.13.4.widows-amd64.msi ；curl-7.83.1

实验人：自动化96 薛荣坤 2196113513

实验中使用的开源包：

http://github.com/davecgh/go-spew/spew；http://github.com/gorilla/mux；http://github.com/joho/godotenv；

实验中使用的工具包：

"crypto/sha256""encoding/hex""encoding/json""fmt""io""log""net/http""os""strconv""strings""sync""time”

实验中的网络端口：http://localhost:8080



*目录*：

[TOC]

## 实验简述

1.基于pow算法挖矿并实现区块链的基本功能

2.基于LevleDB实现数据的KV存储

3.

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j38y1ue9j20k103s3yk.jpg" alt="ooo" style="zoom:50%;" />

## 实验背景

### P2P

对等网络，即对等计算机网络，是一种在对等者之间分配任务和工作负载的分布式应用架构,网络的参与者共享他们所拥有的一部分硬件资源（处理能力、存储能力、网络连接能力、打印机等），这些共享资源通过网络提供服务和内容，能被其它对等节点直接访问而无需经过中间实体。在此网络中的参与者既是资源、服务和内容的提供者，又是资源、服务和内容的获取者。

### 比特币

与大多数货币不同，比特币不依靠特定货币机构发行，它依据特定算法，通过大量的计算产生，比特币经济使用整个P2P网络中众多节点构成的分布式数据库来确认并记录所有的交易行为，并使用密码学的设计来确保货币流通各个环节的安全性。P2P的去中心化特性与算法本身可以确保无法通过大量制造比特币来人为操控币值。基于密码学的设计可以使比特币只能被真实的拥有者转移或支付。

### 区块链

区块链，就是一个又一个区块组成的链条。每一个区块中保存了一定的信息，它们按照各自产生的时间顺序连接成链条。这个链条被保存在所有的服务器中，只要整个系统中有一台服务器可以工作，整条区块链就是安全的。这些服务器在区块链系统中被称为节点，它们为整个区块链系统提供存储空间和算力支持。如果要修改区块链中的信息，必须征得半数以上节点的同意并修改所有节点中的信息，而这些节点通常掌握在不同的主体手中。



## 实验第一部分-基于pow算法挖矿并实现区块链的基本功能

### 实验原理

区块有两种，一个是普通区块，一个就是创世区块。创世区块就是一项区块链项目中的第一个区块。

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j1ji5wsij20d308dgm2.jpg" alt="my" style="zoom: 67%;" />

### 实验内容

配置环境

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j2x1yoy0j20xc0goq5t.jpg" alt="121656034322_.pic" style="zoom:33%;" /><img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j2x4nxxej20m00kidiz.jpg" alt="111656034299_.pic" style="zoom:33%;" />



声明变量

```go
//区块结构体
type Block struct 
{
   PreHash   string
   Hashcode  string
   TimeStamp string
   Diff      int
   Value     string
   Index     int
   Nonce     int
}

//区块链链表
type lian_my struct {
   NextNode *lian_my
   Data     *BLOCK.Block
}

```

这一步用于根据比特币定义我们的哈希值以及新的链表



### 方法

#### 通过自带的数据包生成每一个区块的哈希值

```go
func GenerationHashValue(block Block) string {
   var hashdata = strconv.Itoa(block.Index) + strconv.Itoa(block.Nonce) + strconv.Itoa(block.Diff) + block.TimeStamp
   var hashmy = sha256.New()
   hashmy.Write([]byte(hashdata))
   hashed := hashmy.Sum(nil)
   return hex.EncodeToString(hashed)
}

```

#### 生成之后的区块

```c
func GenerateNextBlock(data string, oldBlock Block) Block {
   var newBlock Block
   newBlock.TimeStamp = time.Now().String()
   newBlock.Diff = 3
   newBlock.Index = oldBlock.Nonce + 1
   newBlock.Value = data
   newBlock.PreHash = oldBlock.Hashcode
   newBlock.Nonce = 0
   newBlock.Hashcode = pow(newBlock.Diff, &newBlock)
   return newBlock
}
```

#### 初始区块声明

```go
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
```

#### pow算法

```go
//pow工作量证明
func pow(diff int, block *Block) string {
   for {
      hashmy := GenerationHashValue(*block)
      if strings.HasPrefix(hashmy, strings.Repeat("0", diff)) {
         return hashmy
         fmt.Println("挖到了一个区块")
      } else {
         block.Nonce++
      }
   }
}
```

函数传入指针，这个相当于是在不断的挖矿，for是一个死循环，用block的信息生成一个哈希值，判断这一次的哈希值是否前面的0满足diff，这里可以直接使用hasprefix（）函数来进行判断，相当的方便。

#### 区块链记录

```go
//创建头节点，保存创世区块
func CreaterHeader(data *BLOCK.Block) *lian_my {
   headerNode := new(lian_my)
   headerNode.NextNode = nil
   headerNode.Data = data
   return headerNode
}

//添加下一个结点
func Addnode(data *BLOCK.Block, node *lian_my) *lian_my {
   var newNode *lian_my = new(lian_my)
   newNode.NextNode = nil
   newNode.Data = data
   node.NextNode = newNode
   return newNode
}

//展示当前所有节点
func ShowNodes(node *lian_my) {
   n := node
   for {
      if n.NextNode == nil {
         fmt.Println(n.Data)
         break
      } else {
         fmt.Println(n.Data)
         n = n.NextNode
      }
   }
}
```

### 调用方法运行结果

#### 初始化第一个区块

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j2p8n0ikj20yr04pt9r.jpg" alt="81656033872_.pic" style="zoom:100%;" />

#### 进行挖矿

![101656033926_.pic](https://tva1.sinaimg.cn/large/e6c9d24ely1h3j2q0cqqij21cv05nq4r.jpg)

#### 广播基本的区块链

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j31dujohj20pq050jrp.jpg" alt="131656034583_.pic" style="zoom:60%;" />

## 实验 第二部分-模拟实现基于LevelDB的KV存储

### 实验原理

leveldb是谷歌两位工程师使用C++实现的k-v存储系统，我们这里希望使用go进行复现， 属于按照key和value存储，用户也是可以重写排序函数，包含了最基本的数据操作接口，put,get,delay.同时多次操作可以认为是一次原子操作，可以用于支持事务。

<img src="/Users/fish/Pictures/Typora/55.png" alt="55" style="zoom: 70%;" />

### 实验代码里的方法及对象

#### 结构体初始化

##### DB结构体

```go
type DB struct {
   path string
   data map[string][]byte
}
```

这里path(字符串类型)用于存储连接的地址，data（byte类型）用于存储kv的键值

##### 迭代器接口和结构体

```go
type Iterator interface {
   Next() bool
   Key() []byte
   Value() []byte
}
type myIterator struct {
   data   []Pair
   index  int
   length int
}
```

​											NEXT判断是否下一个有值， key和value用于遍历键值

##### 键值的结构体

```go
type Pair struct {
   Key   []byte
   Value []byte
}
```

#### 初始化结构体

```go
func NewDefaultIterator(data map[string][]byte) *myIterator {
   my := new(myIterator)
   my.index = -1
   my.length = len(data)
   for k, v := range data {
      p := Pair{[]byte(k),
         v,
      }
      my.data = append(self.data, p)
   }
   return my
}
```

初始化迭代器的默认值并进行遍历

#### 迭代器基本功能的实现

```go
func (self *myIterator) Next() bool {
   if self.index < self.length-1 {
      self.index++
      return true
   }
   return false
}

func (self *myIterator) Key() []byte {
   if self.index == -1 || self.index >= self.length {
      panic(fmt.Errorf("INDEXOUTOFBOUNDERROR"))
   }
   return self.data[self.index].Key
}

func (self *myIterator) Value() []byte {
   if self.index >= self.length {
      panic(fmt.Errorf("INDEXOUTOFBOUNDERROR"))
   }
   return self.data[self.index].Value
}
```

实现下一个是否存在，以及返回value 和key



### 模拟功能实现

####  模拟连接

```go
func New(path string) (*DB, error) {
   my := DB{
      path: path,
      data: make(map[string][]byte),
   }
   return &my, nil
}
```

#### 模拟put,get

```go
func (my *DB) Put(key []byte, value []byte) error {
   my.data[string(key)] = value
   return nil
}


func (my *DB) Get(key []byte) ([]byte, error) {
   if v, ok := my.data[string(key)]; ok {
      return v, nil//如果有则说明可以直接使用
   } else {//如果返回为空，则说明没有
      return nil, 
      fmt.Errorf("Not Found")
   }
}
```

##### 模拟 Del

```go
func (self *DB) Del(key [](byte)) error {
   if _, ok := self.data[string(key)]; ok {
      delete(self.data, string(key))
      return nil
   } else {
      return fmt.Errorf("not Found")
   }
}
```

### KB存储测试

#### 迭代器测试

##### 测试方法：

```go
import (
   "fmt"
   "testing"
)

//迭代器测试
func TestNewDefaultIterator(t *testing.T) {
   data := make(map[string][]byte)
   data["K1"] = []byte("V1")
   data["K2"] = []byte("V2")
   data["K3"] = []byte("V3")
   data["K4"] = []byte("V4")
   my := NewDefaultIterator(data)
   if my.length != 3 {
      t.Fatal()
   }
   for iter.Next() {
      fmt.Printf("%s : %s\n", my.Key(), string(my.Value()))
   }
}
```

测试结果

<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j7q2v9s3j20bz05zwef.jpg" alt="141656044304_.pic" style="zoom: 50%;" />

#### DB测试

##### 测试方法

```go
func Test_leveldb(t *testing.T) {
   db, err := New("")
   check(err)
   err = db.Put([]byte("k1"), []byte("v1"))
   check(err)
   err = db.Put([]byte("k4"), []byte("v4"))
   check(err)
   err = db.Put([]byte("k2"), []byte("v2"))
   check(err)
   err = db.Put([]byte("k1"), []byte("v1"))
   check(err)
   err = db.Put([]byte("k8"), []byte("v8"))
   check(err)
   v, err := db.Get([]byte("k8"))
   fmt.Printf("%s\n\n", v)

   if !bytes.Equal(v, []byte("v8")) {
      t.Fatal()
   }
   v, err = db.Get([]byte("k1"))
   if !bytes.Equal(v, []byte("v1")) {
      t.Fatal()
   }
   //err = db.Del([]byte("k1"))
   //check(err)
   iter := db.Iterator()
   for iter.Next() {
      fmt.Printf("%s - %s \n", string(iter.Key()), string(iter.Value()))
   }
}

func check(err error) {
   if err != nil {
      panic(err)
   }
}
```

##### 测试结果

###### PUT和GET测试<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j7zr2calj203v03da9v.jpg" alt="151656044750_.pic" style="zoom:70%;" />

###### DEL测试				<img src="../Pictures/Typora/161656044755_.pic-6044863.jpg" alt="161656044755_.pic" style="zoom:80%;" />



###### GET不存在元素时测试<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3j801e9itj209v02wgli.jpg" alt="171656044761_.pic" style="zoom:60%;" />



## 实验第3部分-局域网广播和有效区块链

### 实验内容

1.可以在网络端POST指令访问，添加新的比特币交易区块。

2.可以在网络端GET指令访问，查看所有已经添加的交易信息。

### 实验原理

1.实验中使用的开源包：

http://github.com/davecgh/go-spew/spew；

http://github.com/gorilla/mux；

http://github.com/joho/godotenv；

开源包功能：编写web程序的软件包，在控制台格式化输出结果，配置编写.env文件

### 实验方法

#### 声明区块，区块链等基本（和前两部分一样）

注：基本代码和前两部分相同，但在下面处存在区别

```go
var Blockchain []Block
var mutex = &sync.Mutex{}
```

上锁，并且有数组进行存储，同时在有效判别函数中，会抓取所有节点，寻找最长的链，来进行写入。但是在本次试验中因为我在本地并没有其他人的加入，所以我就用简单的python语言大概简述。

```py
def resolve(self) ->bool:
  fujin=self.nodes
  new_chain = None
 	max_length = len(self.chain)
for node in fujin:
   get new_length
    if new_legth>max_length.  and ishashvaild(self)
    	max_length=length
      new_chain=chain
if new_chain:
    self.chain = new_chain
    return true
return false
```



#### 互联网区块链方法

##### HTTP启动

```go
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
```

##### 对区块链数据的操作的初始化

```go
func makeMuxRouter() http.Handler {
   muxRouter := mux.NewRouter()
   muxRouter.HandleFunc("/", handgetblockhain).Methods("GET")
   muxRouter.HandleFunc("/", handerwriteblock).Methods("POST")
   return muxRouter
}
```

#### 查看互联网请求中的内容

```go
func handgetblockhain(w http.ResponseWriter, r *http.Request) {
   bytes, err := json.MarshalIndent(Blockchain, "", "\t")
   if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
   }
   io.WriteString(w, string(bytes))
}
```

##### 验证当前区块是否加入

```go
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
```

​		论证是否是旧的区块+1，以及哈希值是否对应

##### POST，挖到一个区块后进行广播

```go

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

```

### 实验结果

#### 测试主方法

```c
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
```

##### .env配置文件

```GO
ADDR= 8080
```

##### Curl测试命令事例

```apl
curl -H "Content-Type: application/json" -X POST -d"{\"BPM\":10}"“http://localhost:8080”

curl http://localhost:8080
```

#### 实验结果

发送指令<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3jajx6npbj20hx03iglv.jpg" alt="181656047747_.pic" style="zoom:50%;" />

播在局域网中<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3jajyiewhj20na0a80ts.jpg" alt="191656047770_.pic" style="zoom:50%;" />

发送被希望记录的交易信息<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3jak0vktmj20xc0gogpo.jpg" alt="201656047819_.pic" style="zoom: 33%;" />

挖到矿后将其加入了区块链<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3jak378hej20q50is40y.jpg" alt="211656047891_.pic" style="zoom:40%;" />

## 代码扩展部分

我个人是还想使用bee-go metaMast做一个使用区块链交易界面的，但是还是因为个人的问题，代码在golang的前端部分已经完善，但在remix智能公约部分陷进去，出不来了。所以我简要的附上几张图，工程文件里的view会附上我的html css文件。

<div><table frame=void>
	<tr>
        <td><div><center>
        	<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3ja4dhlxej21gw0jqn06.jpg"
                 alt="Typora-Logo"
                 height="120"/>
        	<br>
        	首页
        </center></div></td>    
     	<td><div><center>
    		<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3ja4shupqj21hc0lfadz.jpg"
                 alt="Typora-Logo"
                 height="120"/>
    		<br>
    		查询
        </center></div></td>
	</tr>	
    <tr>	<!--第二行-->
        <td><div><center>
        	<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3ja5b8kgnj21410i0tb8.jpg"
                 alt="Typora-Logo"
                 height="120"/>
        	<br>
        	智能合约
        </center></div></td>    
     	<td><div><center>
    		<img src="https://tva1.sinaimg.cn/large/e6c9d24ely1h3ja7speirj20xc0godma.jpg"
                 alt="Typora-Logo"
                 height="120"/>
    		<br>
    		beego
        </center></div></td>
	</tr>
</table></div>

## 实验心得

在长达两个月的时间，我从GO语言的小白到可以逐步完善自己的想法，从只知道区块链可以炒股到逐渐对其中的原理有了更深的理解，尤其是在广播时候的代码，因为比特币公开的源代码是用c++编写的，所以用go浮现的时候就有了颇多困难。尤其是开发智能合约到最后还要学*Solidity*语言。

因为之前一直都在TI杯比赛中接触代码，但是比赛中大多数都是基于嵌入式环境的硬件系统，无论是ARDUINO,STM32还是ESP82266的开发虽然在调试上但是其中的编程语言都是基于C的，GO和css则完全是面向对象的，尤其是Golang的go get，每次下载一个包都是困难重重，无法cloning竟然还和内网有关。

但是面向对象的有趣在于可以大大减少程序员的调试难度，思路也更有逻辑性。暑假里 我一定要彻底完成我自己的以太坊彩票站。

也感谢沈老师和蔺老师在课堂上对于网络安全的讲解，让我认识到安全学科已经成为了新的行业热门，也了解到网络安全对于社会生产的重要性。



###### 说明：

本实验中的代码均已开源在github；本说明文档首发于[个人博客](www.thedreamfish.cn)