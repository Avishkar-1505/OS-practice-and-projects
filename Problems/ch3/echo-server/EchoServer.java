import java.io.*;
import java.net.*;

public class EchoServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(6013);
            while (true) {
                Socket client = sock.accept();

                try (BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                        PrintWriter out = new PrintWriter(client.getOutputStream(), true)) {

                    String line;
                    while ((line = in.readLine()) != null) { // Read data from the client
                        out.println(line); // Echo the data back to the client
                    }
                    System.out.println("Client disconnected.");
                } catch (IOException e) {
                    System.err.println(e);
                }

                
                client.close();
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}