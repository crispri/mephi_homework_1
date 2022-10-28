#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};

namespace std{

    template<>
    struct hash<SuperKey>{
        std::size_t operator()(const SuperKey& Skey) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            return (hash<std::string>()(Skey.StrPart));
        }

    };


}

void PopulateHashMap(
        std::unordered_map<SuperKey, std::string>& hashMap,
        const std::vector<std::pair<SuperKey, std::string>>& toAdd
);