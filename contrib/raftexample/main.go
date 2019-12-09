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

//#include "Raft.h"
import "C"
import "flag"
import "strings"
import "go.etcd.io/etcd/raft/raftpb"
import "strconv"
import "log"
import "sync"

var wg = &sync.WaitGroup{}

func main() {
	clusterManager := C.makeMainMachine()
	cluster := flag.String("cluster", "http://127.0.0.1:9021", "comma separated cluster peers")
	flag.Parse()
	cluster_list := strings.Split(*cluster, ",")
	for i := 0; i < len(cluster_list); i++ {
		kvport, _ := strconv.Atoi(strings.Split(cluster_list[i], ":")[2])
		kvport = kvport + 1
		C.sendAddMachineEvent(clusterManager)
		wg.Add(1)
		go makeKvStore(cluster_list, i+1, kvport, false)
	}
	wg.Wait()
}

/*
int id: node ID
int port: key-value server port
bool join: join an existing cluster
*/
func makeKvStore(cluster []string, id int, port int, join bool) {
	defer wg.Done()
		log.Printf("hi")
	proposeC := make(chan string)
	defer close(proposeC)
	confChangeC := make(chan raftpb.ConfChange)
	defer close(confChangeC)

	// raft provides a commit stream for the proposals from the http api
	var kvs *kvstore
	getSnapshot := func() ([]byte, error) { return kvs.getSnapshot() }
	commitC, errorC, snapshotterReady := newRaftNode(id, cluster, join, getSnapshot, proposeC, confChangeC)

	kvs = newKVStore(<-snapshotterReady, proposeC, commitC, errorC)



	// the key-value http handler will propose updates to raft
	serveHttpKVAPI(kvs, port, confChangeC, errorC)
}