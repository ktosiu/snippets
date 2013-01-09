package main
import "net"
import "fmt"
import "os"

func main(){
	if len(os.Args) != 2 {
		fmt.Println("Usage:", os.Args[0], "LocalIP")
		return
	}

	captureProtocol("ip4:tcp", os.Args[1])
// 	captureProtocol("ip4:icmp", os.Args[1])
	// captureProtocol("ip4:udp", os.Args[1])
}

func captureProtocol(proto string, localAddr string){
	conn, err := net.ListenPacket(proto, localAddr)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()

	buffer := make([]byte, 1024)
	for {
		n, _, err := conn.ReadFrom(buffer)
		if err != nil {
			fmt.Println(err)
			return
		}
		handlerPacket(proto, buffer[0:n])
	}
}

func handlerPacket(proto string, buffer []byte) {
	if proto == "ip4:icmp" {
		parseICMP(buffer)
	} else if proto == "ip4:tcp" {
		parseTCP(buffer)
	} else if proto == "ip4:udp" {
		parseUDP(buffer)
	} else {
		fmt.Println("Unknown protocol")
	}
}

func parseICMP(buffer []byte){
	typeName := int(buffer[0])
	code := int(buffer[1])
	checkSum := int(buffer[2])<<8 | int(buffer[3])
	id := int(buffer[4])<<8 | int(buffer[5])
	seq := int(buffer[6])<<8 | int(buffer[7])

	fmt.Printf("Type=%d, Code=%d, Check Sum=%d, ID=%d, Seq Number= %d\n", typeName, code, checkSum, id, seq)
}

func parseTCP(buffer []byte){
	srcPort := int(buffer[0])<<8 | int(buffer[1])
	destPort := int(buffer[2])<<8 | int(buffer[3])
	seqNum := int(buffer[4])<<24 | int(buffer[5])<<16 | int(buffer[6])<<8 | int(buffer[7])
	ack := int(buffer[8])<<24 | int(buffer[9])<<16 | int(buffer[10])<<8 | int(buffer[11])
	windowSize := int(buffer[14])<<8 | int(buffer[15])
	checkSum := int(buffer[16])<<8 | int(buffer[17])
	//emergencyPointer := int(buffer[18])<<8 | int(buffer[19])

	fmt.Printf("SrcPort=%d, DestPort=%d, Seq Num=%d, ack=%d, window size= %d, check sum=%d\n", srcPort, destPort, seqNum, ack, windowSize, checkSum)
}

func parseUDP(buffer []byte){

}