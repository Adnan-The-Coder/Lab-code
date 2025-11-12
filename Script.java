import java.io.*;
import java.nio.file.*;
import java.util.stream.*;

public class PrintJavaFiles {
    public static void main(String[] args) {
        Path currentDir = Paths.get("."); // current directory

        try (Stream<Path> stream = Files.list(currentDir)) {
            // Filter only regular files ending with .java
            stream.filter(Files::isRegularFile)
                  .filter(path -> path.toString().endsWith(".java"))
                  .forEach(PrintJavaFiles::printFile);
        } catch (IOException e) {
            System.err.println("Error reading directory: " + e.getMessage());
        }
    }

    private static void printFile(Path file) {
        System.out.println("=".repeat(80));
        System.out.println("FILE: " + file.getFileName());
        System.out.println("=".repeat(80));
        try {
            Files.lines(file).forEach(System.out::println);
        } catch (IOException e) {
            System.err.println("Error reading file " + file + ": " + e.getMessage());
        }
        System.out.println("\n");
    }
}
