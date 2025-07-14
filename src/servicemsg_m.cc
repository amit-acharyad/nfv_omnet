//
// Generated file, do not edit! Created by opp_msgtool 6.1 from servicemsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "servicemsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(ServiceMessage)

ServiceMessage::ServiceMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

ServiceMessage::ServiceMessage(const ServiceMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ServiceMessage::~ServiceMessage()
{
}

ServiceMessage& ServiceMessage::operator=(const ServiceMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ServiceMessage::copy(const ServiceMessage& other)
{
}

void ServiceMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void ServiceMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class ServiceMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    ServiceMessageDescriptor();
    virtual ~ServiceMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ServiceMessageDescriptor)

ServiceMessageDescriptor::ServiceMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ServiceMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

ServiceMessageDescriptor::~ServiceMessageDescriptor()
{
    delete[] propertyNames;
}

bool ServiceMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ServiceMessage *>(obj)!=nullptr;
}

const char **ServiceMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ServiceMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ServiceMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int ServiceMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *ServiceMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int ServiceMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *ServiceMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **ServiceMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ServiceMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ServiceMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ServiceMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ServiceMessage'", field);
    }
}

const char *ServiceMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ServiceMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void ServiceMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceMessage'", field);
    }
}

omnetpp::cValue ServiceMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ServiceMessage' as cValue -- field index out of range?", field);
    }
}

void ServiceMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceMessage'", field);
    }
}

const char *ServiceMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr ServiceMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ServiceMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceMessage *pp = omnetpp::fromAnyPtr<ServiceMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceMessage'", field);
    }
}

Register_Class(ServiceChainRequest)

ServiceChainRequest::ServiceChainRequest(const char *name, short kind) : ::ServiceMessage(name, kind)
{
}

ServiceChainRequest::ServiceChainRequest(const ServiceChainRequest& other) : ::ServiceMessage(other)
{
    copy(other);
}

ServiceChainRequest::~ServiceChainRequest()
{
}

ServiceChainRequest& ServiceChainRequest::operator=(const ServiceChainRequest& other)
{
    if (this == &other) return *this;
    ::ServiceMessage::operator=(other);
    copy(other);
    return *this;
}

void ServiceChainRequest::copy(const ServiceChainRequest& other)
{
    this->enterpriseId = other.enterpriseId;
    this->chainType = other.chainType;
    this->desiredServerCount = other.desiredServerCount;
}

void ServiceChainRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ServiceMessage::parsimPack(b);
    doParsimPacking(b,this->enterpriseId);
    doParsimPacking(b,this->chainType);
    doParsimPacking(b,this->desiredServerCount);
}

void ServiceChainRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ServiceMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->enterpriseId);
    doParsimUnpacking(b,this->chainType);
    doParsimUnpacking(b,this->desiredServerCount);
}

int ServiceChainRequest::getEnterpriseId() const
{
    return this->enterpriseId;
}

void ServiceChainRequest::setEnterpriseId(int enterpriseId)
{
    this->enterpriseId = enterpriseId;
}

const char * ServiceChainRequest::getChainType() const
{
    return this->chainType.c_str();
}

void ServiceChainRequest::setChainType(const char * chainType)
{
    this->chainType = chainType;
}

int ServiceChainRequest::getDesiredServerCount() const
{
    return this->desiredServerCount;
}

void ServiceChainRequest::setDesiredServerCount(int desiredServerCount)
{
    this->desiredServerCount = desiredServerCount;
}

class ServiceChainRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_enterpriseId,
        FIELD_chainType,
        FIELD_desiredServerCount,
    };
  public:
    ServiceChainRequestDescriptor();
    virtual ~ServiceChainRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ServiceChainRequestDescriptor)

ServiceChainRequestDescriptor::ServiceChainRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ServiceChainRequest)), "ServiceMessage")
{
    propertyNames = nullptr;
}

ServiceChainRequestDescriptor::~ServiceChainRequestDescriptor()
{
    delete[] propertyNames;
}

bool ServiceChainRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ServiceChainRequest *>(obj)!=nullptr;
}

const char **ServiceChainRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ServiceChainRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ServiceChainRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int ServiceChainRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_enterpriseId
        FD_ISEDITABLE,    // FIELD_chainType
        FD_ISEDITABLE,    // FIELD_desiredServerCount
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ServiceChainRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "enterpriseId",
        "chainType",
        "desiredServerCount",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ServiceChainRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "enterpriseId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "chainType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "desiredServerCount") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *ServiceChainRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_enterpriseId
        "string",    // FIELD_chainType
        "int",    // FIELD_desiredServerCount
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ServiceChainRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ServiceChainRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ServiceChainRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ServiceChainRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ServiceChainRequest'", field);
    }
}

const char *ServiceChainRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ServiceChainRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return long2string(pp->getEnterpriseId());
        case FIELD_chainType: return oppstring2string(pp->getChainType());
        case FIELD_desiredServerCount: return long2string(pp->getDesiredServerCount());
        default: return "";
    }
}

void ServiceChainRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(string2long(value)); break;
        case FIELD_chainType: pp->setChainType((value)); break;
        case FIELD_desiredServerCount: pp->setDesiredServerCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainRequest'", field);
    }
}

omnetpp::cValue ServiceChainRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return pp->getEnterpriseId();
        case FIELD_chainType: return pp->getChainType();
        case FIELD_desiredServerCount: return pp->getDesiredServerCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ServiceChainRequest' as cValue -- field index out of range?", field);
    }
}

void ServiceChainRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_chainType: pp->setChainType(value.stringValue()); break;
        case FIELD_desiredServerCount: pp->setDesiredServerCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainRequest'", field);
    }
}

const char *ServiceChainRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ServiceChainRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ServiceChainRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainRequest *pp = omnetpp::fromAnyPtr<ServiceChainRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainRequest'", field);
    }
}

Register_Class(ServiceChainAck)

ServiceChainAck::ServiceChainAck(const char *name, short kind) : ::ServiceMessage(name, kind)
{
}

ServiceChainAck::ServiceChainAck(const ServiceChainAck& other) : ::ServiceMessage(other)
{
    copy(other);
}

ServiceChainAck::~ServiceChainAck()
{
}

ServiceChainAck& ServiceChainAck::operator=(const ServiceChainAck& other)
{
    if (this == &other) return *this;
    ::ServiceMessage::operator=(other);
    copy(other);
    return *this;
}

void ServiceChainAck::copy(const ServiceChainAck& other)
{
    this->enterpriseId = other.enterpriseId;
    this->nfviNodeId = other.nfviNodeId;
    this->success = other.success;
    this->messageinfo = other.messageinfo;
}

void ServiceChainAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ServiceMessage::parsimPack(b);
    doParsimPacking(b,this->enterpriseId);
    doParsimPacking(b,this->nfviNodeId);
    doParsimPacking(b,this->success);
    doParsimPacking(b,this->messageinfo);
}

void ServiceChainAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ServiceMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->enterpriseId);
    doParsimUnpacking(b,this->nfviNodeId);
    doParsimUnpacking(b,this->success);
    doParsimUnpacking(b,this->messageinfo);
}

int ServiceChainAck::getEnterpriseId() const
{
    return this->enterpriseId;
}

void ServiceChainAck::setEnterpriseId(int enterpriseId)
{
    this->enterpriseId = enterpriseId;
}

int ServiceChainAck::getNfviNodeId() const
{
    return this->nfviNodeId;
}

void ServiceChainAck::setNfviNodeId(int nfviNodeId)
{
    this->nfviNodeId = nfviNodeId;
}

bool ServiceChainAck::getSuccess() const
{
    return this->success;
}

void ServiceChainAck::setSuccess(bool success)
{
    this->success = success;
}

const char * ServiceChainAck::getMessageinfo() const
{
    return this->messageinfo.c_str();
}

void ServiceChainAck::setMessageinfo(const char * messageinfo)
{
    this->messageinfo = messageinfo;
}

class ServiceChainAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_enterpriseId,
        FIELD_nfviNodeId,
        FIELD_success,
        FIELD_messageinfo,
    };
  public:
    ServiceChainAckDescriptor();
    virtual ~ServiceChainAckDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ServiceChainAckDescriptor)

ServiceChainAckDescriptor::ServiceChainAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ServiceChainAck)), "ServiceMessage")
{
    propertyNames = nullptr;
}

ServiceChainAckDescriptor::~ServiceChainAckDescriptor()
{
    delete[] propertyNames;
}

bool ServiceChainAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ServiceChainAck *>(obj)!=nullptr;
}

const char **ServiceChainAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ServiceChainAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ServiceChainAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ServiceChainAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_enterpriseId
        FD_ISEDITABLE,    // FIELD_nfviNodeId
        FD_ISEDITABLE,    // FIELD_success
        FD_ISEDITABLE,    // FIELD_messageinfo
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ServiceChainAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "enterpriseId",
        "nfviNodeId",
        "success",
        "messageinfo",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ServiceChainAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "enterpriseId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nfviNodeId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "success") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "messageinfo") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ServiceChainAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_enterpriseId
        "int",    // FIELD_nfviNodeId
        "bool",    // FIELD_success
        "string",    // FIELD_messageinfo
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ServiceChainAckDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ServiceChainAckDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ServiceChainAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ServiceChainAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ServiceChainAck'", field);
    }
}

const char *ServiceChainAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ServiceChainAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return long2string(pp->getEnterpriseId());
        case FIELD_nfviNodeId: return long2string(pp->getNfviNodeId());
        case FIELD_success: return bool2string(pp->getSuccess());
        case FIELD_messageinfo: return oppstring2string(pp->getMessageinfo());
        default: return "";
    }
}

void ServiceChainAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(string2long(value)); break;
        case FIELD_nfviNodeId: pp->setNfviNodeId(string2long(value)); break;
        case FIELD_success: pp->setSuccess(string2bool(value)); break;
        case FIELD_messageinfo: pp->setMessageinfo((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainAck'", field);
    }
}

omnetpp::cValue ServiceChainAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return pp->getEnterpriseId();
        case FIELD_nfviNodeId: return pp->getNfviNodeId();
        case FIELD_success: return pp->getSuccess();
        case FIELD_messageinfo: return pp->getMessageinfo();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ServiceChainAck' as cValue -- field index out of range?", field);
    }
}

void ServiceChainAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_nfviNodeId: pp->setNfviNodeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_success: pp->setSuccess(value.boolValue()); break;
        case FIELD_messageinfo: pp->setMessageinfo(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainAck'", field);
    }
}

const char *ServiceChainAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ServiceChainAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ServiceChainAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ServiceChainAck *pp = omnetpp::fromAnyPtr<ServiceChainAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ServiceChainAck'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

