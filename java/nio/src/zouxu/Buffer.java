package zouxu;

import java.nio.ByteBuffer;

public class Buffer {

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        buffer.put((byte)'H');
        buffer.flip();
        while(buffer.hasRemaining()) System.out.println((char)buffer.get());
    }
}
