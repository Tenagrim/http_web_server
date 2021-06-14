# Web Server

###### _HTTP Web Server written in C++98 according to the RFC 7230-7235 standard_

### Features:
- Client-server connection (multiple clients connection available)
- Listening on multiple ports
- Launching several servers
- GET, POST, PUT, HEAD methods
- Error management
- Chunked-requests processing
- Autoindex
- CGI-scripts support
- Client's authorization

This server was implemented as a reference to Nginx HTTP 1.1 compliant.

## Usage

Run `make` inside the repository's directory to build `webserv` binary. 

Program needs the path to configuration file as an argument (example in **conf** directory).

<details>
    <summary>
        Setting up the configuration file
    </summary>
    <br/>
    <p><b>In the main server directive we can specify:</b></p>
    <ul>
        <li>Server ports &emsp;&emsp; 
            <sub>
                <i>listen 80 81</i>
            </sub>
        </li>
        <li>Server name &emsp;&emsp; 
            <sub>
                <i>server_name example.com</i>
            </sub>
        </li>
        <li>Root directory &emsp;&emsp; 
            <sub>
                <i>root /Users/me/cpp_webserver/resources</i>
            </sub>
        </li>
        <li>Custom error pages &emsp;&emsp; 
            <sub>
                <i>error_page 405 /40x.html</i>
            </sub>
        </li>
        <li>On/off autoindex &emsp;&emsp; 
            <sub>
                <i>autoindex on</i>
            </sub>
        </li>
    </ul>
    <p><b>In the location directive we can specify:</b></p>
    <ul>
        <li>Root directory &emsp;&emsp; 
            <sub>
                <i>root /Users/me/cpp_webserver/resources/42_test</i>
            </sub>
        </li>
        <li>Default index page &emsp;&emsp; 
            <sub>
                <i>index index.html</i>
            </sub>
        </li>
        <li>Available methods &emsp;&emsp; 
            <sub>
                <i>limit_except POST GET</i>
            </sub>
        </li>
        <li>Limit of received body size &emsp;&emsp; 
            <sub>
                <i>client_max_body_size 1000</i>
            </sub>
        </li>
        <li>Path to the CGI script interpreter &emsp;&emsp;
            <sub>
                <i>fastcgi_pass /Users/me/cpp_webserver/resources/cgi_tester</i>
            </sub>
        </li>
        <li>Authorization credentials &emsp;&emsp;
            <sub>
                <i>auth_basic user1:qwerty1234</i>
            </sub>
        </li>
    </ul>
</details>
