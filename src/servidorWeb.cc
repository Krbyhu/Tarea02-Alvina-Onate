/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "includes/YASL.h"      // For Socket, ServerSocket, and SocketException
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()
#include "includes/json.hpp"
#include <fstream>

const uint32_t RCVBUFSIZE = 32; 
using json = nlohmann::json;	
std::string pagina(std::string htmline);

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
	//std::cout << "Handling client ";
	try {
		std::cout << sock->getForeignAddress() << ":";
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign address" << std::endl;
	}
	try {
		std::cout << sock->getForeignPort();
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign port" << std::endl;
	}
	std::cout << std::endl;

	// Send received string and receive again until the end of transmission
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;
	int cont = 0;
	std::string buff ="";

	while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
	                                                 // end of transmission
		if(cont == 0) {
			buff = pagina(echoBuffer);
			sock->send(buff.c_str(), 1024);
		}
		cont += 1;
	}
	delete sock;
}

std::string pagina(std::string htmline) {
	
	std::string name ="", line ="", content ="";
	name = htmline.substr (4, htmline.substr(4).find(" "));
      
	std::ifstream opa("WWW-data"+name);
	if(opa.good()) {
		while(getline(opa,line)) {
			content += line+"\n";
		}
	}else {
		std::ifstream opb("WWW-error/404.html");
		while(getline(opb,line)) {
			content += line+"\n";
		}
	}
	return content;
}


int main(int argc, char *argv[]) {

	uint16_t echoServPort;   

	std::ifstream op("bin/config.json");
	json js = json::parse(op);
	std::string ip = js["ip"];
	echoServPort = js["puerto"];
	std::string root_dir = js["root_dir"];
	std::string notFoundFile = js["notFoundFile"];
	std::cout <<"Servidor conectado en ip "+ip+" y puerto "+std::to_string(echoServPort)+"."<< std::endl;
	std::cout <<"Directorio de Páginas: "+root_dir+".\nDirecctorio de Error: "+notFoundFile+"."<<std::endl;

	try {
    		TCPServerSocket servSock(ip,echoServPort);     // Server Socket object
    		for(;;){
      			HandleTCPClient(servSock.accept());
    		}

    
  	} catch (SocketException &e) {
    		std::cerr << e.what() << std::endl;
    		exit(EXIT_FAILURE);
  	}
  	// NOT REACHED

  	return EXIT_SUCCESS;
}
