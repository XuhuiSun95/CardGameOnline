/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "cg_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>



int _kMethodValues[] = {
  Method::GET,
  Method::POST
};
const char* _kMethodNames[] = {
  "GET",
  "POST"
};
const std::map<int, const char*> _Method_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(2, _kMethodValues, _kMethodNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


Table::~Table() throw() {
}


void Table::__set_table_id(const int32_t val) {
  this->table_id = val;
}

void Table::__set_slot(const std::vector<bool> & val) {
  this->slot = val;
}

uint32_t Table::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->table_id);
          this->__isset.table_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->slot.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->slot.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += iprot->readBool(this->slot[_i4]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.slot = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Table::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Table");

  xfer += oprot->writeFieldBegin("table_id", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->table_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("slot", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_BOOL, static_cast<uint32_t>(this->slot.size()));
    std::vector<bool> ::const_iterator _iter5;
    for (_iter5 = this->slot.begin(); _iter5 != this->slot.end(); ++_iter5)
    {
      xfer += oprot->writeBool((*_iter5));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Table &a, Table &b) {
  using ::std::swap;
  swap(a.table_id, b.table_id);
  swap(a.slot, b.slot);
  swap(a.__isset, b.__isset);
}

Table::Table(const Table& other6) {
  table_id = other6.table_id;
  slot = other6.slot;
  __isset = other6.__isset;
}
Table& Table::operator=(const Table& other7) {
  table_id = other7.table_id;
  slot = other7.slot;
  __isset = other7.__isset;
  return *this;
}
void Table::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Table(";
  out << "table_id=" << to_string(table_id);
  out << ", " << "slot=" << to_string(slot);
  out << ")";
}


Card::~Card() throw() {
}


void Card::__set_type(const std::string& val) {
  this->type = val;
}

void Card::__set_value(const std::string& val) {
  this->value = val;
}

uint32_t Card::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->type);
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Card::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Card");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Card &a, Card &b) {
  using ::std::swap;
  swap(a.type, b.type);
  swap(a.value, b.value);
  swap(a.__isset, b.__isset);
}

Card::Card(const Card& other8) {
  type = other8.type;
  value = other8.value;
  __isset = other8.__isset;
}
Card& Card::operator=(const Card& other9) {
  type = other9.type;
  value = other9.value;
  __isset = other9.__isset;
  return *this;
}
void Card::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Card(";
  out << "type=" << to_string(type);
  out << ", " << "value=" << to_string(value);
  out << ")";
}


TRM_OBJ::~TRM_OBJ() throw() {
}


void TRM_OBJ::__set_player_id(const int32_t val) {
  this->player_id = val;
}

void TRM_OBJ::__set_played_cards(const std::vector<Card> & val) {
  this->played_cards = val;
}

uint32_t TRM_OBJ::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->player_id);
          this->__isset.player_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->played_cards.clear();
            uint32_t _size10;
            ::apache::thrift::protocol::TType _etype13;
            xfer += iprot->readListBegin(_etype13, _size10);
            this->played_cards.resize(_size10);
            uint32_t _i14;
            for (_i14 = 0; _i14 < _size10; ++_i14)
            {
              xfer += this->played_cards[_i14].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.played_cards = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TRM_OBJ::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("TRM_OBJ");

  xfer += oprot->writeFieldBegin("player_id", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->player_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("played_cards", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->played_cards.size()));
    std::vector<Card> ::const_iterator _iter15;
    for (_iter15 = this->played_cards.begin(); _iter15 != this->played_cards.end(); ++_iter15)
    {
      xfer += (*_iter15).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TRM_OBJ &a, TRM_OBJ &b) {
  using ::std::swap;
  swap(a.player_id, b.player_id);
  swap(a.played_cards, b.played_cards);
  swap(a.__isset, b.__isset);
}

TRM_OBJ::TRM_OBJ(const TRM_OBJ& other16) {
  player_id = other16.player_id;
  played_cards = other16.played_cards;
  __isset = other16.__isset;
}
TRM_OBJ& TRM_OBJ::operator=(const TRM_OBJ& other17) {
  player_id = other17.player_id;
  played_cards = other17.played_cards;
  __isset = other17.__isset;
  return *this;
}
void TRM_OBJ::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "TRM_OBJ(";
  out << "player_id=" << to_string(player_id);
  out << ", " << "played_cards=" << to_string(played_cards);
  out << ")";
}


