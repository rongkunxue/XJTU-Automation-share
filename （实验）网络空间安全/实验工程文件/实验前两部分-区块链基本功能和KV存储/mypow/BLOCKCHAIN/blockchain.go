package BLOCKCHAIN

import (
	"fmt"
	"mypow/BLOCK"
)

type lian_my struct {
	NextNode *lian_my
	Data     *BLOCK.Block
}

//创建头节点，保存创世区块
func CreaterHeader(data *BLOCK.Block) *lian_my {
	headerNode := new(lian_my)
	headerNode.NextNode = nil
	headerNode.Data = data
	return headerNode
}

func Addnode(data *BLOCK.Block, node *lian_my) *lian_my {
	var newNode *lian_my = new(lian_my)
	newNode.NextNode = nil
	newNode.Data = data
	node.NextNode = newNode
	return newNode
}

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
