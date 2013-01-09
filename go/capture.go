package main
import "net"
import "fmt"
import "os"

func main(){
	if len(os.Args) != 2 {
		fmt.Println("Usage:", os.Args[0], "LocalIP")
		return
	}

	//captureProtocol("ip4:tcp", os.Args[1])
	captureProtocol("ip4:icmp", os.Args[1])
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

	} else if proto == "ip4:udp" {

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