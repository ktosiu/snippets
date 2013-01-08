package main
import "net"
import "fmt"
import "os"

func main(){
	if len(os.Args) != 2 {
		fmt.Println("Usage:", os.Args[0], "Local IP")
		return
	}
 
	addr, err := net.ResolveIPAddr("ip", os.Args[1])
	if err != nil {
		fmt.Println(err)
		return
	}

	conn, err := net.ListenIP("ip4:tcp", addr)
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
		}
		fmt.Println(buffer[0:n])
	}
}