#include "common.h"
#include "flvparser.h"

int main() {
    const char* filePath = "../doc/source.200kbps.768x320.flv";
    cout << "hello flv parser" << endl;

    ifstream ifs(filePath);
	if(!ifs.is_open())
	{
		cerr << "ifstream open file error!\n";
		return -1;
	}

    shared_ptr<void> autofree(nullptr, [&](void *) {
        cout << "auto free file" << endl;
        ifs.close();
    });

    ifs.seekg(0, ios_base::end); // 先把文件输入流指针定位到文档末尾来获取文档的长度
    int length = ifs.tellg();
	ifs.seekg(ios_base::beg);  //再将指针定位到文档开头来进行读取

	char* buff = new char[length + 1](); //开辟一个buff
    ifs.read(buff, length + 1); // 将内容读取到buff中
    FLVParser parser(std::move(buff), length);
    parser.Parse();

    return 0;
}
