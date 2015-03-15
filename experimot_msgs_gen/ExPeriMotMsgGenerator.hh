#ifndef EXPERIMOTMSGGENERATOR_H
#define EXPERIMOTMSGGENERATOR_H

#include <google/protobuf/compiler/code_generator.h>
#include <string>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {
class GeneratorContext;

/// \addtogroup experimot_msgs Messages
/// \{

/// \brief Google protobuf message generator for experimot::msgs
class ExPeriMotMsgGenerator : public CodeGenerator
{
public: ExPeriMotMsgGenerator(const std::string &_name);

public: virtual ~ExPeriMotMsgGenerator();

  public: virtual bool Generate(const FileDescriptor* file,
                const string& parameter,
                OutputDirectory *directory,
                string* error) const;

  // private: GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(experimotGenerator);
};

/// \}
}
}
}
}
#endif