// Copyright 2015 The etcd Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package main

import (
	"encoding/json"
	"log"
	"sync"
	"time"
)

// a key-value store backed by raft
type kvstorep struct {
	mu           sync.RWMutex
	kvStore      map[string]string // current committed key-value pairs
	proposedVals map[string]time.Time
}

func newPKVStore() *kvstorep {
	s := &kvstorep{kvStore: make(map[string]string), proposedVals: make(map[string]time.Time)}
	// replay log into key-value map
	s.readCommits()
	// read commits from raft into kvStore map until error
	go s.readCommits()
	return s
}

func (s *kvstorep) Lookup(key string) (string, bool) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	v, ok := s.kvStore[key]
	return v, ok
}

func (s *kvstorep) Propose(k string, v string) {
	log.Printf("proposed - key: %s, value: %s", k, v)
}

func (s *kvstorep) readCommits() {
	for {
		log.Print("hello")
	}
}

func (s *kvstorep) getSnapshot() ([]byte, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return json.Marshal(s.kvStore)
}

func (s *kvstorep) recoverFromSnapshot(snapshot []byte) error {
	var store map[string]string
	if err := json.Unmarshal(snapshot, &store); err != nil {
		return err
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	s.kvStore = store
	return nil
}
