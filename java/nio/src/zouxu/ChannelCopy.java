package zouxu;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;

public class ChannelCopy {
    public static void main(String[] argv) throws IOException {
        ReadableByteChannel source = Channels.newChannel(System.in);
        WritableByteChannel dest = Channels.newChannel(System.out);

        channelCopy(source, dest);

        source.close();
        dest.close();
    }

    private static void channelCopy(ReadableByteChannel source, WritableByteChannel dest) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
        while(source.read(buffer) != -1) {
            buffer.flip();

            dest.write(buffer);
            buffer.compact();
        }

        // EOF will leave buffer in fill state
        buffer.flip();

        // Make sure that the buffer is fully drained
        while (buffer.hasRemaining()) {
            dest.write(buffer);
        }
    }
}
