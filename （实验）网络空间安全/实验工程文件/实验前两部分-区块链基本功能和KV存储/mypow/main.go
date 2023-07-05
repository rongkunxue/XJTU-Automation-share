package main

import (
	"mypow/BLOCK"
	"mypow/BLOCKCHAIN"
)

func main() {
	println("打印当前链表")
	first := BLOCK.GenerateFirstBlock("10ETH")
	second := BLOCK.GenerateNextBlock("20EFT", first)
	third := BLOCK.GenerateNextBlock("5ETH", second)
	header := BLOCKCHAIN.CreaterHeader(&first)
	BLOCKCHAIN.Addnode(&second, header)
	BLOCKCHAIN.Addnode(&third, header)
	BLOCKCHAIN.ShowNodes(header)
}
