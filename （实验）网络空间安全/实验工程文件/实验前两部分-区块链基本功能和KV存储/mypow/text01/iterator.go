package text01

import "fmt"

type Iterator interface {
	Next() bool
	Key() []byte
	Value() []byte
}

type Pair struct {
	Key   []byte
	Value []byte
}

type myIterator struct {
	data   []Pair
	index  int
	length int
}

func NewDefaultIterator(data map[string][]byte) *myIterator {
	my := new(myIterator)
	my.index = -1
	my.length = len(data)
	for m, n := range data {
		p := Pair{[]byte(m),
			n,
		}
		my.data = append(my.data, p)
	}
	return my
}

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
