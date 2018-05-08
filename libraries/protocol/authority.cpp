#include <steemit/protocol/authority.hpp>
#include <boost/regex.hpp>

namespace steemit {
    namespace protocol {

// authority methods
        void authority::add_authority(const public_key_type &k, weight_type w) {
            key_auths[k] = w;
        }

        void authority::add_authority(const account_name_type &k, weight_type w) {
            account_auths[k] = w;
        }

        vector<public_key_type> authority::get_keys() const {
            vector<public_key_type> result;
            result.reserve(key_auths.size());
            for (const auto &k : key_auths)
                result.push_back(k.first);
            return result;
        }

        bool authority::is_impossible() const {
            uint64_t auth_weights = 0;
            for (const auto &item : account_auths) auth_weights += item.second;
            for (const auto &item : key_auths) auth_weights += item.second;
            return auth_weights < weight_threshold;
        }

        uint32_t authority::num_auths() const { return account_auths.size() + key_auths.size(); }

        void authority::clear() {
            account_auths.clear();
            key_auths.clear();
        }

        void authority::validate() const {
            for (const auto &item : account_auths) {
                FC_ASSERT(is_valid_account_name(item.first));
            }
        }


        bool is_valid_account_name(const string &name) {
            //test length
            size_t length = mbstowcs(NULL, name.c_str(), name.length());
            if (length < STEEMIT_MIN_ACCOUNT_NAME_LENGTH)
                return false;

            if (length > STEEMIT_MAX_ACCOUNT_NAME_LENGTH)
                return false;

            boost::regex rg("^[a-zA-Z0-9_\u4e00-\u9fa5]+$");
            boost::smatch sm;
            if (boost::regex_match(name, sm, rg)) {
                return true;
            }
            return false;
        }

        bool operator==(const authority &a, const authority &b) {
            return (a.weight_threshold == b.weight_threshold) &&
                   (a.account_auths == b.account_auths) &&
                   (a.key_auths == b.key_auths);
        }

    }
} // steemit::protocol
