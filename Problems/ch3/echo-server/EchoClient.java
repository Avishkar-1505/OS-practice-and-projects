import java.io.*;
import java.net.*;

public class EchoClient {
    public static void main(String[] args) {
        try {
            /* make connection to server socket */
            Socket sock = new Socket("127.0.0.1", 6013);
            PrintWriter out = new PrintWriter(sock.getOutputStream(), true);
            BufferedReader bin = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in)) ;

            String userInput;

            while ((userInput = stdIn.readLine()) != null) {
                out.println(userInput); // sending input to server
                System.out.println("echo: " + bin.readLine()); // printing the server response
            }

            
            sock.close();
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
