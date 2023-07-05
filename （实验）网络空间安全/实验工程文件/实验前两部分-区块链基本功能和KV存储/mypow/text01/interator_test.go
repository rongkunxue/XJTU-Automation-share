package text01

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
	iter := NewDefaultIterator(data)
	if iter.length != 4 {
		t.Fatal()
	}
	for iter.Next() {
		fmt.Printf("%s : %s\n", iter.Key(), string(iter.Value()))
	}
}
