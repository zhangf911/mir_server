#ifndef mir_proto_adl_h_adata_header_define
#define mir_proto_adl_h_adata_header_define

#include <adata.hpp>

namespace mir {
  struct msg_header
  {
    uint32_t size;
    uint32_t type;
    msg_header()
    :    size(0),
    type(0)
    {}
  };

  struct echo_message
  {
    ::std::string msg;
    echo_message()
    {}
  };

}

namespace adata
{
  template<typename stream_ty>
  ADATA_INLINE void read( stream_ty& stream, ::mir::msg_header& value)
  {
    ::std::size_t offset = stream.read_length();
    uint64_t tag = 0;
    read(stream,tag);
    if(stream.error()){return;}
    int32_t len_tag = 0;
    read(stream,len_tag);
    if(stream.error()){return;}

    if(tag&1ULL)    {fix_read(stream,value.size);{if(stream.error()){stream.trace_error("size",-1);return;}}}
    if(tag&2ULL)    {fix_read(stream,value.type);{if(stream.error()){stream.trace_error("type",-1);return;}}}
    if(len_tag >= 0)
    {
      ::std::size_t read_len = stream.read_length() - offset;
      ::std::size_t len = (::std::size_t)len_tag;
      if(len > read_len) stream.skip_read(len - read_len);
    }
  }

  template <typename stream_ty>
  ADATA_INLINE void skip_read(stream_ty& stream, ::mir::msg_header* value)
  {
    (value);
    skip_read_compatible(stream);
  }

  ADATA_INLINE int32_t size_of(const ::mir::msg_header& value)
  {
    int32_t size = 0;
    uint64_t tag = 3ULL;
    {
      size += fix_size_of(value.size);
    }
    {
      size += fix_size_of(value.type);
    }
    size += size_of(tag);
    size += size_of(size + size_of(size));
    return size;
  }

  template<typename stream_ty>
  ADATA_INLINE void write(stream_ty& stream , const ::mir::msg_header&value)
  {
    uint64_t tag = 3ULL;
    write(stream,tag);
    if(stream.error()){return;}
    write(stream,size_of(value));
    if(stream.error()){return;}
    {fix_write(stream,value.size);{if(stream.error()){stream.trace_error("size",-1);return;}}}
    {fix_write(stream,value.type);{if(stream.error()){stream.trace_error("type",-1);return;}}}
    return;
  }

  template<typename stream_ty>
  ADATA_INLINE void read( stream_ty& stream, ::mir::echo_message& value)
  {
    ::std::size_t offset = stream.read_length();
    uint64_t tag = 0;
    read(stream,tag);
    if(stream.error()){return;}
    int32_t len_tag = 0;
    read(stream,len_tag);
    if(stream.error()){return;}

    if(tag&1ULL)
    {
      uint32_t len = check_read_size(stream);
      {if(stream.error()){stream.trace_error("msg",-1);return;}}
      value.msg.resize(len);
      stream.read((char *)value.msg.data(),len);
      {if(stream.error()){stream.trace_error("msg",-1);return;}}
    }
    if(len_tag >= 0)
    {
      ::std::size_t read_len = stream.read_length() - offset;
      ::std::size_t len = (::std::size_t)len_tag;
      if(len > read_len) stream.skip_read(len - read_len);
    }
  }

  template <typename stream_ty>
  ADATA_INLINE void skip_read(stream_ty& stream, ::mir::echo_message* value)
  {
    (value);
    skip_read_compatible(stream);
  }

  ADATA_INLINE int32_t size_of(const ::mir::echo_message& value)
  {
    int32_t size = 0;
    uint64_t tag = 0ULL;
    if(!value.msg.empty()){tag|=1ULL;}
    if(tag&1ULL)
    {
      int32_t len = (int32_t)(value.msg).size();
      size += size_of(len);
      size += len;
    }
    size += size_of(tag);
    size += size_of(size + size_of(size));
    return size;
  }

  template<typename stream_ty>
  ADATA_INLINE void write(stream_ty& stream , const ::mir::echo_message&value)
  {
    uint64_t tag = 0ULL;
    if(!value.msg.empty()){tag|=1ULL;}
    write(stream,tag);
    if(stream.error()){return;}
    write(stream,size_of(value));
    if(stream.error()){return;}
    if(tag&1ULL)
    {
      uint32_t len = (uint32_t)(value.msg).size();
      write(stream,len);
      stream.write((value.msg).data(),len);
      {if(stream.error()){stream.trace_error("msg",-1);return;}}
    }
    return;
  }

}

#endif
