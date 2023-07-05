package text01

import (
	"fmt"
	"testing"
)

func Test_leveldb(t *testing.T) {
	db, err := New("")
	check(err)
	err = db.Put([]byte("k1"), []byte("v1"))
	check(err)
	err = db.Put([]byte("k4"), []byte("v4"))
	check(err)
	err = db.Put([]byte("k2"), []byte("v2"))
	check(err)
	v, err := db.Get([]byte("k8"))
	fmt.Printf("%s\n\n", v)

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
