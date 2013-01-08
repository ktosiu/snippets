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
	// captureProtocol("ip4:icmp", os.Args[1])
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
	fmt.Println(proto)
	fmt.Println(buffer)
}