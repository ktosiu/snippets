package zouxu;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

/**
 * Created by zouivex on 8/9/15.
 */
public class FileHole {
    public static void main(String[] argv) throws IOException {
        File temp = File.createTempFile("file_with_hole", null);
        RandomAccessFile file = new RandomAccessFile(temp, "rw");
        FileChannel channel = file.getChannel();

        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);

        putData(0, buffer, channel);
        putData(5000000, buffer, channel);
        putData(50000, buffer, channel);

        channel.close();
        file.close();
    }

    private static void putData(int position, ByteBuffer buffer, FileChannel channel) throws IOException {
        String s = "*<-- location " + position;

        buffer.clear();
        buffer.put(s.getBytes());
        buffer.flip();

        channel.position(position);
        channel.write(buffer);
    }
}
