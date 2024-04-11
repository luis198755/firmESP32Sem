#include <WiFi.h>
#include <WebServer.h>
#include <SD.h>
#include <FS.h>

/**
 * WebServer 
 * @author miguemx
*/
class WebServerESP32 {
    public:
        WebServerESP32(int port) : server(port) {}

        void connectToWiFi(const char* ssid, const char* password) {
            Serial.println("Connecting to WiFi...");
            WiFi.begin(ssid, password);

            while (WiFi.status() != WL_CONNECTED) {
                delay(1000);
                Serial.println("Establishing connection to WiFi..");
            }

            Serial.println("Connected to WiFi");
        }

        void startServer() {
            server.on("/", HTTP_GET, [this]() {
                handleIndex();
            });

            server.on("/json", HTTP_GET, [this]() {
                handleJson();
            });

            server.on("/program", HTTP_POST, [this]() {
                handleProgram();
            });

            server.on("/hello", HTTP_GET, [this]() {
                server.send(200, "text/plain", "Server is working!");
            });

            server.on("/about", HTTP_GET, [this]() {
                server.send(200, "text/plain", "Server is working!");
            });

            server.begin();
            Serial.println("HTTP server started");
        }

        void handleClient() {
            server.handleClient();
        }

        void initSDCard(int csPin) {
            if (!SD.begin(csPin)) {
                Serial.println("Card Mount Failed");
                return;
            }
            Serial.println("SD Card initialized.");
        }

    private:
        WebServer server;

        void handleIndex() {
            File file = SD.open("/web/index.html");
            if ( file ) {
                server.streamFile( file, "text/html" );
                file.close();
            }
            else {
                handle404();
            }
        }

        void handleJson() {
            File file = SD.open("/web/json.html");
            if ( file ) {
                server.streamFile( file, "text/html" );
                file.close();
            }
            else {
                handle404();
            }
        }

        void handleAbout() {
            File file = SD.open("web/about.html");
            if ( file ) {
                server.streamFile( file, "text/html" );
                file.close();
            }
            else {
                handle404();
            }
        }

        void handleProgram() {
            if (server.hasArg("params") == false) { // Check if the body received is plain text
                handle404(); // Handle case where there's no body in the request
                return;
            }

            // Extract the body of the POST request, which should be your JSON string
            String postBody = server.arg("params");

            // Now you can write the `postBody` to your `config/program.json` file
            File file = SD.open("/config/program.json", "w");
            if (file) {
                file.print(postBody); // Write the JSON string to the file
                file.close();
                server.send(200, "application/json", "{\"message\": \"Program updated successfully\"}"); // Send a success response
            } else {
                handle404(); // Handle case where file couldn't be opened
            }
        }

        void handle404() {
            server.send( 404, "text/plain", "File not found");
        }
};