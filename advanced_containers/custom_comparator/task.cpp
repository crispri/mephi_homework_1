#include "task.h"

bool operator <(const SuperKey& lhs, const SuperKey& rhs) {
    return lhs.StrPart<=rhs.StrPart;

}

void PopulateMap(
        std::map<SuperKey, std::string>& map,
        const std::vector<std::pair<SuperKey, std::string>>& toAdd
) {
    for (auto i: toAdd) {
        map[i.first] = i.second;

    }
}


