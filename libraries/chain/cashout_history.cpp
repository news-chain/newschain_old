//
// Created by boy on 18-3-9.
//
#include <steemit/chain/cashout_history.hpp>
#include <boost/filesystem.hpp>
namespace steemit {
    namespace chain {




        void cashout_history::cacheJsonByName_toPath(boost::filesystem::fstream &stream) {
            std::string cachePath;

            const static std::string path_cache_accounts = "cache/regist.txt";
            const static std::string path_cache_postComment = "cache/postComment.txt";
            const static std::string path_cache_reader = "cache/reader.txt";
            const static std::string path_cache_shareComment = "cache/shareComment.txt";
            const static std::string path_cache_writeToComment = "cache/writeToComment.txt";
            const static std::string path_cache_teacher = "cache/teacher.txt";


            if (!boost::filesystem::exists("cache")) {
                if (!boost::filesystem::create_directories("cache")) {
                    elog("create cache directory error!");
                } else{
                    elog("create cache directory!");
                }
            }

            switch (m_type) {
                case historyType::regist: {
                    cacheRegist(path_cache_accounts);
                    break;
                }
                case historyType::postComment: {
//                    boost::filesystem::fstream fstream(path_cache_postComment, std::ios_base::out);
//                    fstream << m_orderId << "," << m_payout << "\n";
//                    fstream.close();
                    stream << m_orderId << "," << m_payout << "," << fc::time_point::now().sec_since_epoch() << "000\n";
                    break;
                }
                case historyType::reader: {
                    cacheOther(path_cache_reader);
                    break;
                }
                case historyType::shareComment: {
                    cacheOther(path_cache_shareComment);
                    break;
                }
                case historyType::write_to_comment: {
                    cacheOther(path_cache_writeToComment);
                    break;
                }case historyType::teacher: {
//                    boost::filesystem::fstream fstream(path_cache_teacher, std::ios_base::out);
//                    fstream << m_userId << "," << m_parentId << "," << m_payout  << "\n";
//                    fstream.close();
                    uint64_t time = fc::time_point::now().sec_since_epoch();
                    stream << m_userId << "," << m_parentId << "," << m_payout << "," << time << "000," << m_orderId << "\n";
                    break;
                }
                default: {

                }
            }


        }


        void cashout_history::cacheRegist(std::string path) {


        }




        void cashout_history::cacheOther(std::string path) {
        }





        namespace http {
            using boost::asio::ip::tcp;

            bool asyc_postData(std::string url, std::string data, std::string contentType, std::string &reponse_data) {

                if(url.substr(0, 7) == "http://") {
                    url = url.substr(7, url.length());
                }

                std::string host;
                std::string port;
                std::string page;
                auto find_port = url.find(':');
                auto find_path = url.find('/');
                if (find_port == -1) {
                    port = "80";
                    host = url.substr(0, find_path);
                } else {
                    port = url.substr(find_port + 1, find_path - find_port - 1);
                    host = url.substr(0, find_port);
                }
                page = url.substr(find_path, url.length());

                boost::asio::io_service io_service;
                //如果io_service存在复用的情况
                if (io_service.stopped())
                    io_service.reset();

                wlog("send = host:${h}, port=${p}", ("h", host)("p", port));
                // 从dns取得域名下的所有ip
                tcp::resolver resolver(io_service);
                tcp::resolver::query query(host, port);
                tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

                // 尝试连接到其中的某个ip直到成功
                tcp::socket socket(io_service);
                boost::asio::connect(socket, endpoint_iterator);

                // Form the request. We specify the "Connection: close" header so that the
                // server will close the socket after transmitting the response. This will
                // allow us to treat all data up until the EOF as the content.
                wlog("write data to request_stream1");
                boost::asio::streambuf request;
                std::ostream request_stream(&request);
                request_stream << "POST " << page << " HTTP/1.0\r\n";
                request_stream << "Host: " << host << ":" << port << "\r\n";
                request_stream << "Accept: application/json;charset=utf-8\r\n";
                request_stream << "Content-Length: " << data.length() << "\r\n";
                request_stream << "Content-Type: "<< contentType <<"\r\n\r\n";
//                request_stream << "Connection: close\r\n\r\n";
                request_stream << data;

                // Send the request.
                wlog("write data to request_stream2");
                boost::asio::write(socket, request);
                wlog("write data to request_stream3");
                // Read the response status line. The response streambuf will automatically
                // grow to accommodate the entire line. The growth may be limited by passing
                // a maximum size to the streambuf constructor.
                boost::asio::streambuf response;
                boost::asio::read_until(socket, response, "\r\n");

                // Check that response is OK.
                std::istream response_stream(&response);
                std::string http_version;
                response_stream >> http_version;
                unsigned int status_code;
                response_stream >> status_code;
                std::string status_message;
                std::getline(response_stream, status_message);
                wlog("write data to request_stream code = ${c}", ("c",  status_code));
                if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
                    reponse_data = "Invalid response";
                    return -2;
                }
                // 如果服务器返回非200都认为有错,不支持301/302等跳转
                if (status_code != 200) {
                    reponse_data = "Response returned with status code != 200 ";
//                        return status_code;
                }

                // 传说中的包头可以读下来了
                std::string header;
                std::vector<std::string> headers;
                while (std::getline(response_stream, header) && header != "\r"){
                    wlog("head = ${h}", ("h", header));
                    headers.push_back(header);
                }


                // 读取所有剩下的数据作为包体
                boost::system::error_code error;
                while (boost::asio::read(socket, response,
                                         boost::asio::transfer_at_least(1), error)) {
                }

                //响应有数据
                if (response.size()) {
                    std::istream response_stream(&response);
                    std::istreambuf_iterator<char> eos;
                    reponse_data = std::string(std::istreambuf_iterator<char>(response_stream), eos);
                }

                if (error != boost::asio::error::eof) {
                    reponse_data = error.message();
                }

                return true;
            }
        }

    }
}