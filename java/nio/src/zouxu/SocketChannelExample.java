package zouxu;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class SocketChannelExample {

    public static void main(String args[]) throws IOException {
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
        serverSocketChannel.configureBlocking(false);

        ServerSocket serverSocket = serverSocketChannel.socket();
        serverSocket.bind(new InetSocketAddress(8000));

        Selector selector = Selector.open();
        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

        ByteBuffer buffer = ByteBuffer.allocate(1024);

        while (true) {
            // Blocking here until some channels are available.
            selector.select();

            Set selectedKeys = selector.selectedKeys();
            Iterator it = selectedKeys.iterator();
            while(it.hasNext()) {
                SelectionKey key = (SelectionKey)it.next();
                if((key.readyOps() & SelectionKey.OP_ACCEPT) == SelectionKey.OP_ACCEPT) {
                    ServerSocketChannel ssc = (ServerSocketChannel)key.channel();
                    SocketChannel sc = ssc.accept();
                    sc.configureBlocking(false);

                    System.out.println("Connection established, with peer: " + sc.getRemoteAddress());

                    sc.register(selector, SelectionKey.OP_READ);
                }
                else if((key.readyOps() & SelectionKey.OP_READ) == SelectionKey.OP_READ) {
                    buffer.clear();
                    SocketChannel sc = (SocketChannel)key.channel();

                    sc.read(buffer);
                    // Flip is very important. Otherwise the bellow print messages code will fail
                    buffer.flip();

                    while(buffer.hasRemaining()) {
                        System.out.print((char) buffer.get());
                    }
                }
                else if((key.readyOps() & SelectionKey.OP_WRITE) == SelectionKey.OP_WRITE) {
                    // handle Write
                }

                it.remove();
            }
        }
    }
}
