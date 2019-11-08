#include <curl/curl.h>
#include <stdexcept>
#include <string>

namespace curl {
    const char* version() {
        return curl_version();
    }

    time_t get_date(const std::string& str) {
        //time_t time;
        return curl_getdate(str.c_str(), nullptr);
    }

    namespace {
        static bool is_global_inited = false;
    }

    namespace helper {
        static int string_writer(char *data, size_t size, size_t nmemb, void* writerData)
        {
            if(writerData == NULL)
                return 0;
            ((std::string*)writerData)->append(data, size*nmemb);    
            return int(size * nmemb);
        }
        static int file_writer(char *data, size_t size, size_t nmemb, void* writerData)
        {
            if(writerData == NULL)
                return 0;
            fwrite(data, size, nmemb, (FILE*)writerData);
            return int(size * nmemb);
        }
        
    }

    // Single directed List for C-strings 
    class slist {
        curl_slist* handle_;
        public:

        slist() {
            handle_ = nullptr;
        }

        slist(const curl_slist* inlist) {
            curl_slist* handle_ = nullptr;
            curl_slist* tmp;

            while(inlist) {
                tmp = curl_slist_append(handle_, inlist->data);

                if(!tmp) {
                    curl_slist_free_all(handle_);
                    throw std::bad_alloc();
                }

                handle_ = tmp;
                inlist = inlist->next;
            }
        }

        ~slist() {
            if(handle_) {
                curl_slist_free_all(handle_);
            }
        }

        char* front() {
            return handle_->data;
        }
        
        void push_front(const char* str) {
            curl_slist* old = handle_;
            handle_ = curl_slist_append(nullptr, str);
            if(!handle_) {
                handle_ = old;
                throw std::bad_alloc();
            }
            else {
                handle_->next = old;
            }
        }

        void pop_front() {
            if(!handle_)
                throw std::underflow_error("pop an empty slist from the front");
            curl_slist* next = handle_->next;
            handle_->next = nullptr;
            curl_slist_free_all(handle_);
            handle_ = next;
        }

        char* back() {
            curl_slist* item;
            /* if caller passed us a NULL, return now */
            if(!handle_)
                return nullptr;

            /* loop through to find the last item */
            item = handle_;
            while(item->next) {
                item = item->next;
            }
            return item->data;
        }

        void pop_back() {
            /* if caller passed us a NULL, throw an exception */
            if(!handle_)
                throw std::underflow_error("pop an empty slist from the back");

            curl_slist* item, *item2 = nullptr;
            /* loop through to find the last item */
            item = handle_;
            while(item->next) {
                item2 = item;
                item = item->next;
            }

            curl_slist_free_all(item);

            if(item == handle_) {
                handle_ = nullptr;
            }

            if(item2) {
                item2->next = nullptr;
            }
        }

        void push_back(const char* str) {
            handle_ = curl_slist_append(handle_, str);
        }

        // int size() {
        
        // }

        // bool empty() {

        // }

        curl_slist* data() {
            return handle_;
        }
    };

    class easy {
        CURL* handle_;
        char error_buffer_[CURL_ERROR_SIZE];
        CURLcode code_;
        public:
        // constructor
        easy() {
            if(!is_global_inited) {
                code_ = curl_global_init(CURL_GLOBAL_ALL);
                if(code_ != CURLE_OK) {
                    throw std::runtime_error(curl_easy_strerror(code_));
                }
                is_global_inited = true;
            }
            handle_ = curl_easy_init();
            code_ = curl_easy_setopt(handle_, CURLOPT_ERRORBUFFER, error_buffer_);
            if(code_ != CURLE_OK) {
                throw std::runtime_error(curl_easy_strerror(code_));
            }
        }

        ~easy() {
            curl_easy_cleanup(handle_);
        }

        template <typename T>
        void set_option(CURLoption opt, T param) {
            code_ = curl_easy_setopt(handle_, opt, param);
            if(code_ != CURLE_OK) {
                throw std::runtime_error(error_buffer_);
            }
        }

        void set_option(CURLoption opt, slist& param) {
            code_ = curl_easy_setopt(handle_, opt, param.data());
            if(code_ != CURLE_OK) {
                throw std::runtime_error(error_buffer_);
            }
        }

        void set_option(CURLoption opt, std::string& param) {
            code_ = curl_easy_setopt(handle_, opt, param.c_str());
            if(code_ != CURLE_OK) {
                throw std::runtime_error(error_buffer_);
            }
        }

        template <typename T>
        void getinfo(CURLINFO info, T& arg) {
            curl_easy_getinfo(handle_, info, &arg);
        }

        void perform() {
            code_ = curl_easy_perform(handle_);
            if(code_ != CURLE_OK) {
                throw std::runtime_error(error_buffer_);
            }
        }


        void reset() {
            curl_easy_reset(handle_);
        }

        const CURLcode& code() {
            return code_;
        }

        const char* error() {
            return error_buffer_;
        }

        CURL* handle() {
            return handle_;
        }
    };
}