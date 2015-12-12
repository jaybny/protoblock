#ifndef fantasybit_datapersist_h
#define fantasybit_datapersist_h

#include <fstream>
#include <iostream>
#include <cstdio>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message.h>
#include <fcntl.h>

namespace fantasybit
{

template<class T>
class Writer
{
	std::ofstream mFs;
	google::protobuf::io::OstreamOutputStream *_OstreamOutputStream;
	google::protobuf::io::CodedOutputStream *_CodedOutputStream;
    bool gd = false;
public:
	typedef T indata;
	Writer(const std::string &file,std::ios::openmode flags = 0) :
		mFs(file,std::ios::out | std::ios::binary | flags)
	{
		if (mFs.good())
        {
            gd = true;
            _OstreamOutputStream = new google::protobuf::io::OstreamOutputStream(&mFs);
            _CodedOutputStream = new google::protobuf::io::CodedOutputStream(_OstreamOutputStream);
        }
	}
    
    bool good() const {
        return gd;
    }

	inline void operator()(const google::protobuf::Message &msg)
	{
        if ( !good() )
        {
            std::cout << "Writer<> error !good \n";
            return;
        }

		_CodedOutputStream->WriteVarint32(msg.ByteSize());
		if ( !msg.SerializeToCodedStream(_CodedOutputStream) )
			std::cout << "SerializeToCodedStream error \n";
	}
    
	~Writer()
	{
        if ( _CodedOutputStream)
            delete _CodedOutputStream;
        if ( _OstreamOutputStream )
            delete _OstreamOutputStream;
		mFs.close();
	}
};
	
template<class T>
class Reader
{
	std::ifstream mFs;
	google::protobuf::io::IstreamInputStream *_IstreamInputStream = nullptr;
	google::protobuf::io::CodedInputStream *_CodedInputStream = nullptr;
    bool gd = false;
public:
	Reader(const std::string &file, std::ios::openmode flags = 0):
		mFs(file,std::ios::in | std::ios::binary | flags)
	{
		if (mFs.good())
        {
            gd = true;
            _IstreamInputStream = new google::protobuf::io::IstreamInputStream(&mFs);
            _CodedInputStream = new google::protobuf::io::CodedInputStream(_IstreamInputStream);
        }
	}

    bool good() const {
        return gd;
    }

	bool ReadNext(T &msg)
	{
        if ( !good() )
        {
            std::cerr << "Reader<> error !good\n";
            return false;
        }

		uint32_t size;

		bool ret;
		if ( (ret = _CodedInputStream->ReadVarint32(&size)) )
		{	
			google::protobuf::io::CodedInputStream::Limit msgLimit = _CodedInputStream->PushLimit(size);
			ret = msg.ParseFromCodedStream(_CodedInputStream);
			_CodedInputStream->PopLimit(msgLimit);
		}

		return ret;
	}
	
	~Reader()
	{
		if (_CodedInputStream != nullptr )
   			delete _CodedInputStream;
		if (_IstreamInputStream != nullptr)
			delete _IstreamInputStream;
   		mFs.close();
	}
};

}

#endif
