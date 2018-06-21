#include <locale>
#include <variant>
#include <vector>
#include <type_traits>

namespace INISerializer {

namespace SerializationFunctions {

#include "templateSpecialization/util.h"
#include "templateSpecialization/integers.h"
#include "templateSpecialization/floatingpoint.h"
#include "templateSpecialization/misc.h"
#include "templateSpecialization/pair.h"
#include "templateSpecialization/tuple.h"
#include "templateSpecialization/array.h"
#include "templateSpecialization/vector.h"

}
}
