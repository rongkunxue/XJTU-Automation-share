package text01

import "fmt"

//面向对象的结构体
//连接的地址和KV的键值
type DB struct {
	path string
	data map[string][]byte
}

func New(path string) (*DB, error) {
	my := DB{
		path: path,
		data: make(map[string][]byte),
	}
	return &my, nil
}

func (my *DB) Put(key []byte, value []byte) error {
	my.data[string(key)] = value
	return nil
}

func (my *DB) Get(key []byte) ([]byte, error) {
	if v, ok := my.data[string(key)]; ok {
		return v, nil
	} else {
		return nil,
			fmt.Errorf("Not Found")
	}
}

func (self *DB) Del(key [](byte)) error {
	if _, ok := self.data[string(key)]; ok {
		delete(self.data, string(key))
		return nil
	} else {
		return fmt.Errorf("not Found")
	}
}

func (self *DB) Iterator() Iterator {
	return NewDefaultIterator(self.data)
}
