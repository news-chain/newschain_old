//
// Created by boy on 18-3-8.
//

#ifndef STEEM_LEVEL_HPP
#define STEEM_LEVEL_HPP


namespace steemit{
    namespace protocol{
        struct userLevel{
//            LevelType type;
            uint32_t readerLevel = 1;
            uint32_t readerPercent = 0;

            uint32_t writeLevel = 1;
            uint32_t writePercent = 0;

            uint32_t shareLevel = 1;
            uint32_t sharePercent = 0;


            userLevel operator = (const userLevel &a){
                readerPercent = a.readerPercent;
                writePercent = a.writePercent;
                sharePercent = a.sharePercent;
                updateLevel();
                return *this;
            }


            void updateLevel(){
                auto &json = configManager::getInstance()->getLevelInfo();

                std::map<uint32_t , uint32_t> rl = json["reader"];
                for(auto itr = rl.begin(); itr != rl.end(); itr++){
                    if(itr->second < readerPercent){
                        continue;
                    }
                    else{
                        readerLevel = itr->first;
                        break;
                    }
                }

                std::map<uint32_t , uint32_t> sl = json["share"];
                for(auto itr = sl.begin(); itr != sl.end(); itr++){
                    if(itr->second < sharePercent){
                        continue;
                    }
                    else{
                        shareLevel = itr->first;
                        break;
                    }
                }

                std::map<uint32_t , uint32_t> writel = json["write"];
                for(auto itr = writel.begin(); itr != writel.end(); itr++){
                    if(itr->second < writePercent){
                        continue;
                    } else{
                        writeLevel = itr->first;
                        break;
                    }
                }
            }
        };
    }




}

//DECLARE_OPERATION_TYPE(steemit::protocol::userLevel)


FC_REFLECT(steemit::protocol::userLevel, (readerLevel)(readerPercent)(writeLevel)(writePercent)(shareLevel)(sharePercent))

#endif //STEEM_LEVEL_HPP
