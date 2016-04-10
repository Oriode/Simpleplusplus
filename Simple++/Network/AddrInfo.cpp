#include "AddrInfo.h"


namespace Network {



	AddrInfo::AddrInfo(const AddrInfo & addrInfo){
		this -> ai_addr = NULL;
		this -> ai_canonname = NULL;
		setNext(NULL);
		*this = addrInfo;
	}

	AddrInfo::AddrInfo(const struct addrinfo & addrInfo){
		this -> ai_addr = NULL;
		this -> ai_canonname = NULL;
		setNext(NULL);
		*this = addrInfo;
	}

	AddrInfo::AddrInfo(SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/){
		setSockType(sockType);
		setIpFamily(ipFamily);
		setFlags(0);
		setNext(NULL);
		setProtocol(0);
		this -> ai_addrlen = 0;
		this -> ai_addr = NULL;
		this -> ai_canonname = NULL;

	}


	
	AddrInfo::AddrInfo(const AddrInfo & addrInfo, SockType sockType, IpFamily ipFamily, unsigned short port) {
		*this = ( ( struct addrinfo )addrInfo );
		setSockType(sockType);
		setIpFamily(ipFamily);
		setSockAddrPort(port);
	}

	AddrInfo::AddrInfo(const String & ip, const String & service, SockType sockType, IpFamily ipFamily /*= IpFamily::Undefined*/) {
		setSockType(sockType);
		setIpFamily(ipFamily);

		struct addrinfo * addrResults;
		if ( getaddrinfo(ip.getData(), service.getData(), this, &addrResults) ) {
			error(String("Unable to retrieve address info on address  ") << ip << "@" << service);
		}

		*this = *addrResults;
		freeaddrinfo(addrResults);
	}

	AddrInfo::AddrInfo(const String & ip, const String & service, const AddrInfo & hints) {
		struct addrinfo * addrResults;
		if ( getaddrinfo(ip.getData(), service.getData(), &hints, &addrResults) ) {
			error(String("Unable to retrieve address info on address  ") << ip << "@" << service);
		}

		*this = *addrResults;
		freeaddrinfo(addrResults);
	}

	AddrInfo::~AddrInfo() {
		freeaddrinfo(this);
	}

	AddrInfo & AddrInfo::operator=(const AddrInfo & addrInfo){
		*this = ((struct addrinfo)addrInfo);
		return *this;
	}

	AddrInfo & AddrInfo::operator=(const struct addrinfo & addrInfo){
		this -> ai_family = addrInfo.ai_family;
		this -> ai_flags = addrInfo.ai_flags;
		this -> ai_next = addrInfo.ai_next;
		this -> ai_protocol = addrInfo.ai_protocol;
		this -> ai_socktype = addrInfo.ai_socktype;


		setSockAddr(addrInfo.ai_addr, addrInfo.ai_addrlen);

		if (addrInfo.ai_canonname != NULL){
			size_t textSize = strlen(addrInfo.ai_canonname);
			this -> ai_canonname = new char[textSize + 1];
			memcpy(this -> ai_canonname, addrInfo.ai_canonname, textSize + 1);
		}
		else
			this -> ai_canonname = NULL;

		return *this;
	}

	void AddrInfo::setNext(struct addrinfo * next){
		this -> ai_next = next;
	}

	size_t AddrInfo::getSockAddrLen() const{
		return this -> ai_addrlen;
	}


	void AddrInfo::setIpFamily(IpFamily ipFamily){
		this -> ai_family = (int)ipFamily;
	}

	void AddrInfo::setSockType(SockType sockType){
		this -> ai_socktype = (int)sockType;
	}

	void AddrInfo::setFlags(int flags){
		this -> ai_flags = flags;
	}

	int AddrInfo::getFlags() const{
		return this -> ai_flags;
	}

	void AddrInfo::addFlag(Flags flags){
		this -> ai_flags |= (unsigned int)flags;
	}

	IpFamily AddrInfo::getIpFamily() const{
		return (IpFamily) this -> ai_family;
	}

	IpFamily AddrInfo::getIpFamily(const std::string & ip){
		for (auto i = ip.begin(); i != ip.end(); i++){
			if (*i == ':') return IpFamily::IPv6;
			if (*i == '.') return IpFamily::IPv4;
		}
		return IpFamily::Undefined;
	}

	int AddrInfo::getProtocol() const{
		return this -> ai_protocol;
	}

	const struct sockaddr * AddrInfo::getSockAddr() const{
		return this -> ai_addr;
	}

	SockType AddrInfo::getSockType() const{
		return (SockType) this -> ai_socktype;
	}

	void AddrInfo::setCanonName(const String & name){
		delete[] this -> ai_canonname;
		if (name.getSize()){
			this -> ai_canonname = new char[name.getSize() + 1];
			memcpy(this -> ai_canonname, name.getData(), name.getSize() + 1);
		}
		else {
			this -> ai_canonname = NULL;
		}
	}

	void AddrInfo::setProtocol(int protocol){
		this -> ai_protocol = protocol;
	}

	void AddrInfo::newSockAddr(size_t newSize){
		this -> ai_addrlen = newSize;
		delete[] this -> ai_addr;
		if (newSize){
			this -> ai_addr = (struct sockaddr *) new char[newSize];
			memset(this -> ai_addr, 0, newSize);
		}
		else {
			this -> ai_addr = NULL;
		}
	}

	const String & AddrInfo::getSockTypeS() const{
		static const String tcp("TCP");
		static const String udp("UDP");


		return ((SockType)this -> ai_socktype == SockType::TCP ? tcp : udp );
	}

	const String & AddrInfo::getIpFamilyS() const{
		static const String ipv4("IPv4");
		static const String ipv6("IPv6");
		static const String ipUndefined("IPv4 & IPv6");


		switch ((IpFamily)this -> ai_family){
		case IpFamily::IPv4:
			return ipv4;
		case IpFamily::IPv6:
			return ipv6;
		case IpFamily::Undefined:
			return ipUndefined;
		}
		return String::null;
	}

	const struct addrinfo * AddrInfo::getAddrInfoStruct() const{
		return this;
	}



	String AddrInfo::getNameInfo(const struct sockaddr & sockAddr, size_t sockAddrLen){
		char nameBuffer[100];
		if (getnameinfo(&sockAddr, (socklen_t)sockAddrLen, nameBuffer, sizeof(nameBuffer), NULL, 0, NI_NUMERICHOST) == SOCKET_ERROR)
			return String::null;
		else
			return String(nameBuffer);
	}

	String AddrInfo::getNameInfo(const struct addrinfo & addrInfo){
		if ( addrInfo.ai_addr )
			return getNameInfo(*addrInfo.ai_addr, addrInfo.ai_addrlen);
		else
			return String::null;
	}

	String AddrInfo::getNameInfo() const{
		return getNameInfo(*this);
	}


	unsigned short AddrInfo::getPort(const struct sockaddr & sockAddr){
		if (sockAddr.sa_family == AF_INET)
			return ntohs(((struct sockaddr_in &)sockAddr).sin_port);
		else
			return ntohs(((struct sockaddr_in6 &)sockAddr).sin6_port);
	}

	unsigned short AddrInfo::getPort() const{
		if ( this -> ai_addr )
			return getPort(*this -> ai_addr);
		else
			return 0;
	}



	void AddrInfo::setSockAddr(const struct sockaddr * sockAddr, size_t sockAddrLen){
		if (sockAddr == NULL){
			delete[] this -> ai_addr;
			this -> ai_addr = NULL;
			this -> ai_addrlen = 0;
		} else {
			if (this -> ai_addrlen != sockAddrLen){
				delete[] this -> ai_addr;
				this -> ai_addr = (sockaddr *) new char[sockAddrLen];
				this -> ai_addrlen = sockAddrLen;
			} 
			memcpy(this -> ai_addr, sockAddr, sockAddrLen);
		}
		
	}

	void AddrInfo::setSockAddrPort(unsigned short port){
		if (this -> ai_addr != NULL){
			if (this -> ai_addr -> sa_family == AF_INET)
				((struct sockaddr_in*)this -> ai_addr) -> sin_port = htons(port);
			else
				((struct sockaddr_in6*)this -> ai_addr) -> sin6_port = htons(port);
		}
	}

	void AddrInfo::setSockAddrPort(const struct sockaddr * sockAddr){
		if (this -> ai_addr != NULL){
			if (this -> ai_addr -> sa_family == AF_INET)
				((struct sockaddr_in*)this -> ai_addr) -> sin_port = ((struct sockaddr_in*)sockAddr) -> sin_port;
			else
				((struct sockaddr_in6*)this -> ai_addr) -> sin6_port = ((struct sockaddr_in6*)sockAddr) -> sin6_port;
		}
	}

}
