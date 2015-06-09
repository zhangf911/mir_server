// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: opcodes.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "opcodes.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* msg_header_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  msg_header_reflection_ = NULL;
const ::google::protobuf::Descriptor* msg_t_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  msg_t_reflection_ = NULL;
const ::google::protobuf::Descriptor* msg_login_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  msg_login_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* opcode_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* op_error_code_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_opcodes_2eproto() {
  protobuf_AddDesc_opcodes_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "opcodes.proto");
  GOOGLE_CHECK(file != NULL);
  msg_header_descriptor_ = file->message_type(0);
  static const int msg_header_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_header, size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_header, type_),
  };
  msg_header_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      msg_header_descriptor_,
      msg_header::default_instance_,
      msg_header_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_header, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_header, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(msg_header));
  msg_t_descriptor_ = file->message_type(1);
  static const int msg_t_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_t, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_t, data_),
  };
  msg_t_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      msg_t_descriptor_,
      msg_t::default_instance_,
      msg_t_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_t, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_t, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(msg_t));
  msg_login_descriptor_ = file->message_type(2);
  static const int msg_login_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_login, account_),
  };
  msg_login_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      msg_login_descriptor_,
      msg_login::default_instance_,
      msg_login_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_login, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg_login, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(msg_login));
  opcode_descriptor_ = file->enum_type(0);
  op_error_code_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_opcodes_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    msg_header_descriptor_, &msg_header::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    msg_t_descriptor_, &msg_t::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    msg_login_descriptor_, &msg_login::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_opcodes_2eproto() {
  delete msg_header::default_instance_;
  delete msg_header_reflection_;
  delete msg_t::default_instance_;
  delete msg_t_reflection_;
  delete msg_login::default_instance_;
  delete msg_login_reflection_;
}

void protobuf_AddDesc_opcodes_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ropcodes.proto\"(\n\nmsg_header\022\014\n\004size\030\001 "
    "\002(\005\022\014\n\004type\030\002 \002(\005\"#\n\005msg_t\022\014\n\004type\030\001 \002(\005"
    "\022\014\n\004data\030\002 \002(\014\"\034\n\tmsg_login\022\017\n\007account\030\001"
    " \002(\t*\032\n\006opcode\022\020\n\014cg_login_csq\020\001*\035\n\rop_e"
    "rror_code\022\014\n\010nonerror\020\000", 183);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "opcodes.proto", &protobuf_RegisterTypes);
  msg_header::default_instance_ = new msg_header();
  msg_t::default_instance_ = new msg_t();
  msg_login::default_instance_ = new msg_login();
  msg_header::default_instance_->InitAsDefaultInstance();
  msg_t::default_instance_->InitAsDefaultInstance();
  msg_login::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_opcodes_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_opcodes_2eproto {
  StaticDescriptorInitializer_opcodes_2eproto() {
    protobuf_AddDesc_opcodes_2eproto();
  }
} static_descriptor_initializer_opcodes_2eproto_;
const ::google::protobuf::EnumDescriptor* opcode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return opcode_descriptor_;
}
bool opcode_IsValid(int value) {
  switch(value) {
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* op_error_code_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return op_error_code_descriptor_;
}
bool op_error_code_IsValid(int value) {
  switch(value) {
    case 0:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int msg_header::kSizeFieldNumber;
const int msg_header::kTypeFieldNumber;
#endif  // !_MSC_VER

msg_header::msg_header()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:msg_header)
}

void msg_header::InitAsDefaultInstance() {
}

msg_header::msg_header(const msg_header& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:msg_header)
}

void msg_header::SharedCtor() {
  _cached_size_ = 0;
  size_ = 0;
  type_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

msg_header::~msg_header() {
  // @@protoc_insertion_point(destructor:msg_header)
  SharedDtor();
}

void msg_header::SharedDtor() {
  if (this != default_instance_) {
  }
}

void msg_header::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* msg_header::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return msg_header_descriptor_;
}

const msg_header& msg_header::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_opcodes_2eproto();
  return *default_instance_;
}

msg_header* msg_header::default_instance_ = NULL;

msg_header* msg_header::New() const {
  return new msg_header;
}

void msg_header::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<msg_header*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(size_, type_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool msg_header::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:msg_header)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 size = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &size_)));
          set_has_size();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }

      // required int32 type = 2;
      case 2: {
        if (tag == 16) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:msg_header)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:msg_header)
  return false;
#undef DO_
}

void msg_header::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:msg_header)
  // required int32 size = 1;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->size(), output);
  }

  // required int32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->type(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:msg_header)
}

::google::protobuf::uint8* msg_header::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg_header)
  // required int32 size = 1;
  if (has_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->size(), target);
  }

  // required int32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->type(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg_header)
  return target;
}

int msg_header::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 size = 1;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->size());
    }

    // required int32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void msg_header::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const msg_header* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const msg_header*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void msg_header::MergeFrom(const msg_header& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_size()) {
      set_size(from.size());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void msg_header::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg_header::CopyFrom(const msg_header& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg_header::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void msg_header::Swap(msg_header* other) {
  if (other != this) {
    std::swap(size_, other->size_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata msg_header::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = msg_header_descriptor_;
  metadata.reflection = msg_header_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int msg_t::kTypeFieldNumber;
const int msg_t::kDataFieldNumber;
#endif  // !_MSC_VER

msg_t::msg_t()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:msg_t)
}

void msg_t::InitAsDefaultInstance() {
}

msg_t::msg_t(const msg_t& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:msg_t)
}

void msg_t::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  type_ = 0;
  data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

msg_t::~msg_t() {
  // @@protoc_insertion_point(destructor:msg_t)
  SharedDtor();
}

void msg_t::SharedDtor() {
  if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete data_;
  }
  if (this != default_instance_) {
  }
}

void msg_t::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* msg_t::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return msg_t_descriptor_;
}

const msg_t& msg_t::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_opcodes_2eproto();
  return *default_instance_;
}

msg_t* msg_t::default_instance_ = NULL;

msg_t* msg_t::New() const {
  return new msg_t;
}

void msg_t::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    type_ = 0;
    if (has_data()) {
      if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        data_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool msg_t::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:msg_t)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 type = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_data;
        break;
      }

      // required bytes data = 2;
      case 2: {
        if (tag == 18) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:msg_t)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:msg_t)
  return false;
#undef DO_
}

void msg_t::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:msg_t)
  // required int32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }

  // required bytes data = 2;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->data(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:msg_t)
}

::google::protobuf::uint8* msg_t::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg_t)
  // required int32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }

  // required bytes data = 2;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->data(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg_t)
  return target;
}

int msg_t::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }

    // required bytes data = 2;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->data());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void msg_t::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const msg_t* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const msg_t*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void msg_t::MergeFrom(const msg_t& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_data()) {
      set_data(from.data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void msg_t::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg_t::CopyFrom(const msg_t& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg_t::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void msg_t::Swap(msg_t* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(data_, other->data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata msg_t::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = msg_t_descriptor_;
  metadata.reflection = msg_t_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int msg_login::kAccountFieldNumber;
#endif  // !_MSC_VER

msg_login::msg_login()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:msg_login)
}

void msg_login::InitAsDefaultInstance() {
}

msg_login::msg_login(const msg_login& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:msg_login)
}

void msg_login::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  account_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

msg_login::~msg_login() {
  // @@protoc_insertion_point(destructor:msg_login)
  SharedDtor();
}

void msg_login::SharedDtor() {
  if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete account_;
  }
  if (this != default_instance_) {
  }
}

void msg_login::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* msg_login::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return msg_login_descriptor_;
}

const msg_login& msg_login::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_opcodes_2eproto();
  return *default_instance_;
}

msg_login* msg_login::default_instance_ = NULL;

msg_login* msg_login::New() const {
  return new msg_login;
}

void msg_login::Clear() {
  if (has_account()) {
    if (account_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      account_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool msg_login::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:msg_login)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string account = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_account()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->account().data(), this->account().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "account");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:msg_login)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:msg_login)
  return false;
#undef DO_
}

void msg_login::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:msg_login)
  // required string account = 1;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "account");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->account(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:msg_login)
}

::google::protobuf::uint8* msg_login::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg_login)
  // required string account = 1;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "account");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->account(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg_login)
  return target;
}

int msg_login::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string account = 1;
    if (has_account()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->account());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void msg_login::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const msg_login* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const msg_login*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void msg_login::MergeFrom(const msg_login& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_account()) {
      set_account(from.account());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void msg_login::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg_login::CopyFrom(const msg_login& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg_login::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void msg_login::Swap(msg_login* other) {
  if (other != this) {
    std::swap(account_, other->account_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata msg_login::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = msg_login_descriptor_;
  metadata.reflection = msg_login_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
