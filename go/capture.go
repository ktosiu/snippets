package main
import "net"
import "fmt"

func main(){
	conn, err := net.ListenPacket("ip4:icmp", "0.0.0.0")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()
	
	buffer := make([]byte, 256)
	for {
		_, _, err := conn.ReadFrom(buffer)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(buffer)
	}
}