//
// Generated file, do not edit! Created by opp_msgtool 6.1 from nfvMessages.msg.
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
#include "nfvMessages_m.h"

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

Register_Class(NfvMessage)

NfvMessage::NfvMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

NfvMessage::NfvMessage(const NfvMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

NfvMessage::~NfvMessage()
{
}

NfvMessage& NfvMessage::operator=(const NfvMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void NfvMessage::copy(const NfvMessage& other)
{
}

void NfvMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void NfvMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class NfvMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    NfvMessageDescriptor();
    virtual ~NfvMessageDescriptor();

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

Register_ClassDescriptor(NfvMessageDescriptor)

NfvMessageDescriptor::NfvMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(NfvMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

NfvMessageDescriptor::~NfvMessageDescriptor()
{
    delete[] propertyNames;
}

bool NfvMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NfvMessage *>(obj)!=nullptr;
}

const char **NfvMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NfvMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NfvMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int NfvMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *NfvMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int NfvMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *NfvMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **NfvMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *NfvMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int NfvMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NfvMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NfvMessage'", field);
    }
}

const char *NfvMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NfvMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void NfvMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NfvMessage'", field);
    }
}

omnetpp::cValue NfvMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NfvMessage' as cValue -- field index out of range?", field);
    }
}

void NfvMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NfvMessage'", field);
    }
}

const char *NfvMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr NfvMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NfvMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NfvMessage *pp = omnetpp::fromAnyPtr<NfvMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NfvMessage'", field);
    }
}

Register_Enum(VnfType, (VnfType::VNF_TYPE_UNKNOWN, VnfType::VNF_TYPE_FIREWALL, VnfType::VNF_TYPE_LOADBALANCER, VnfType::VNF_TYPE_SERVER));

Register_Class(VnfDeploymentRequest)

VnfDeploymentRequest::VnfDeploymentRequest(const char *name, short kind) : ::NfvMessage(name, kind)
{
}

VnfDeploymentRequest::VnfDeploymentRequest(const VnfDeploymentRequest& other) : ::NfvMessage(other)
{
    copy(other);
}

VnfDeploymentRequest::~VnfDeploymentRequest()
{
    delete [] this->backendServerIps;
}

VnfDeploymentRequest& VnfDeploymentRequest::operator=(const VnfDeploymentRequest& other)
{
    if (this == &other) return *this;
    ::NfvMessage::operator=(other);
    copy(other);
    return *this;
}

void VnfDeploymentRequest::copy(const VnfDeploymentRequest& other)
{
    this->vnfName = other.vnfName;
    this->vnfType = other.vnfType;
    this->requestId = other.requestId;
    this->cpuRequest = other.cpuRequest;
    this->memoryRequest = other.memoryRequest;
    this->bandwidthRequest = other.bandwidthRequest;
    this->vnfIpAddress = other.vnfIpAddress;
    this->firewallLbVip = other.firewallLbVip;
    delete [] this->backendServerIps;
    this->backendServerIps = (other.backendServerIps_arraysize==0) ? nullptr : new int[other.backendServerIps_arraysize];
    backendServerIps_arraysize = other.backendServerIps_arraysize;
    for (size_t i = 0; i < backendServerIps_arraysize; i++) {
        this->backendServerIps[i] = other.backendServerIps[i];
    }
}

void VnfDeploymentRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::NfvMessage::parsimPack(b);
    doParsimPacking(b,this->vnfName);
    doParsimPacking(b,this->vnfType);
    doParsimPacking(b,this->requestId);
    doParsimPacking(b,this->cpuRequest);
    doParsimPacking(b,this->memoryRequest);
    doParsimPacking(b,this->bandwidthRequest);
    doParsimPacking(b,this->vnfIpAddress);
    doParsimPacking(b,this->firewallLbVip);
    b->pack(backendServerIps_arraysize);
    doParsimArrayPacking(b,this->backendServerIps,backendServerIps_arraysize);
}

void VnfDeploymentRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::NfvMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->vnfName);
    doParsimUnpacking(b,this->vnfType);
    doParsimUnpacking(b,this->requestId);
    doParsimUnpacking(b,this->cpuRequest);
    doParsimUnpacking(b,this->memoryRequest);
    doParsimUnpacking(b,this->bandwidthRequest);
    doParsimUnpacking(b,this->vnfIpAddress);
    doParsimUnpacking(b,this->firewallLbVip);
    delete [] this->backendServerIps;
    b->unpack(backendServerIps_arraysize);
    if (backendServerIps_arraysize == 0) {
        this->backendServerIps = nullptr;
    } else {
        this->backendServerIps = new int[backendServerIps_arraysize];
        doParsimArrayUnpacking(b,this->backendServerIps,backendServerIps_arraysize);
    }
}

const char * VnfDeploymentRequest::getVnfName() const
{
    return this->vnfName.c_str();
}

void VnfDeploymentRequest::setVnfName(const char * vnfName)
{
    this->vnfName = vnfName;
}

VnfType VnfDeploymentRequest::getVnfType() const
{
    return this->vnfType;
}

void VnfDeploymentRequest::setVnfType(VnfType vnfType)
{
    this->vnfType = vnfType;
}

int VnfDeploymentRequest::getRequestId() const
{
    return this->requestId;
}

void VnfDeploymentRequest::setRequestId(int requestId)
{
    this->requestId = requestId;
}

double VnfDeploymentRequest::getCpuRequest() const
{
    return this->cpuRequest;
}

void VnfDeploymentRequest::setCpuRequest(double cpuRequest)
{
    this->cpuRequest = cpuRequest;
}

double VnfDeploymentRequest::getMemoryRequest() const
{
    return this->memoryRequest;
}

void VnfDeploymentRequest::setMemoryRequest(double memoryRequest)
{
    this->memoryRequest = memoryRequest;
}

double VnfDeploymentRequest::getBandwidthRequest() const
{
    return this->bandwidthRequest;
}

void VnfDeploymentRequest::setBandwidthRequest(double bandwidthRequest)
{
    this->bandwidthRequest = bandwidthRequest;
}

int VnfDeploymentRequest::getVnfIpAddress() const
{
    return this->vnfIpAddress;
}

void VnfDeploymentRequest::setVnfIpAddress(int vnfIpAddress)
{
    this->vnfIpAddress = vnfIpAddress;
}

int VnfDeploymentRequest::getFirewallLbVip() const
{
    return this->firewallLbVip;
}

void VnfDeploymentRequest::setFirewallLbVip(int firewallLbVip)
{
    this->firewallLbVip = firewallLbVip;
}

size_t VnfDeploymentRequest::getBackendServerIpsArraySize() const
{
    return backendServerIps_arraysize;
}

int VnfDeploymentRequest::getBackendServerIps(size_t k) const
{
    if (k >= backendServerIps_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)backendServerIps_arraysize, (unsigned long)k);
    return this->backendServerIps[k];
}

void VnfDeploymentRequest::setBackendServerIpsArraySize(size_t newSize)
{
    int *backendServerIps2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = backendServerIps_arraysize < newSize ? backendServerIps_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        backendServerIps2[i] = this->backendServerIps[i];
    for (size_t i = minSize; i < newSize; i++)
        backendServerIps2[i] = 0;
    delete [] this->backendServerIps;
    this->backendServerIps = backendServerIps2;
    backendServerIps_arraysize = newSize;
}

void VnfDeploymentRequest::setBackendServerIps(size_t k, int backendServerIps)
{
    if (k >= backendServerIps_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)backendServerIps_arraysize, (unsigned long)k);
    this->backendServerIps[k] = backendServerIps;
}

void VnfDeploymentRequest::insertBackendServerIps(size_t k, int backendServerIps)
{
    if (k > backendServerIps_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)backendServerIps_arraysize, (unsigned long)k);
    size_t newSize = backendServerIps_arraysize + 1;
    int *backendServerIps2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        backendServerIps2[i] = this->backendServerIps[i];
    backendServerIps2[k] = backendServerIps;
    for (i = k + 1; i < newSize; i++)
        backendServerIps2[i] = this->backendServerIps[i-1];
    delete [] this->backendServerIps;
    this->backendServerIps = backendServerIps2;
    backendServerIps_arraysize = newSize;
}

void VnfDeploymentRequest::appendBackendServerIps(int backendServerIps)
{
    insertBackendServerIps(backendServerIps_arraysize, backendServerIps);
}

void VnfDeploymentRequest::eraseBackendServerIps(size_t k)
{
    if (k >= backendServerIps_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)backendServerIps_arraysize, (unsigned long)k);
    size_t newSize = backendServerIps_arraysize - 1;
    int *backendServerIps2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        backendServerIps2[i] = this->backendServerIps[i];
    for (i = k; i < newSize; i++)
        backendServerIps2[i] = this->backendServerIps[i+1];
    delete [] this->backendServerIps;
    this->backendServerIps = backendServerIps2;
    backendServerIps_arraysize = newSize;
}

class VnfDeploymentRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vnfName,
        FIELD_vnfType,
        FIELD_requestId,
        FIELD_cpuRequest,
        FIELD_memoryRequest,
        FIELD_bandwidthRequest,
        FIELD_vnfIpAddress,
        FIELD_firewallLbVip,
        FIELD_backendServerIps,
    };
  public:
    VnfDeploymentRequestDescriptor();
    virtual ~VnfDeploymentRequestDescriptor();

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

Register_ClassDescriptor(VnfDeploymentRequestDescriptor)

VnfDeploymentRequestDescriptor::VnfDeploymentRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VnfDeploymentRequest)), "NfvMessage")
{
    propertyNames = nullptr;
}

VnfDeploymentRequestDescriptor::~VnfDeploymentRequestDescriptor()
{
    delete[] propertyNames;
}

bool VnfDeploymentRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VnfDeploymentRequest *>(obj)!=nullptr;
}

const char **VnfDeploymentRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VnfDeploymentRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VnfDeploymentRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int VnfDeploymentRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vnfName
        0,    // FIELD_vnfType
        FD_ISEDITABLE,    // FIELD_requestId
        FD_ISEDITABLE,    // FIELD_cpuRequest
        FD_ISEDITABLE,    // FIELD_memoryRequest
        FD_ISEDITABLE,    // FIELD_bandwidthRequest
        FD_ISEDITABLE,    // FIELD_vnfIpAddress
        FD_ISEDITABLE,    // FIELD_firewallLbVip
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_backendServerIps
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *VnfDeploymentRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vnfName",
        "vnfType",
        "requestId",
        "cpuRequest",
        "memoryRequest",
        "bandwidthRequest",
        "vnfIpAddress",
        "firewallLbVip",
        "backendServerIps",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int VnfDeploymentRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vnfName") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "vnfType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "requestId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "cpuRequest") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "memoryRequest") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "bandwidthRequest") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "vnfIpAddress") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "firewallLbVip") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "backendServerIps") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *VnfDeploymentRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_vnfName
        "VnfType",    // FIELD_vnfType
        "int",    // FIELD_requestId
        "double",    // FIELD_cpuRequest
        "double",    // FIELD_memoryRequest
        "double",    // FIELD_bandwidthRequest
        "int",    // FIELD_vnfIpAddress
        "int",    // FIELD_firewallLbVip
        "int",    // FIELD_backendServerIps
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **VnfDeploymentRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_vnfType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *VnfDeploymentRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_vnfType:
            if (!strcmp(propertyName, "enum")) return "VnfType";
            return nullptr;
        default: return nullptr;
    }
}

int VnfDeploymentRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_backendServerIps: return pp->getBackendServerIpsArraySize();
        default: return 0;
    }
}

void VnfDeploymentRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_backendServerIps: pp->setBackendServerIpsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VnfDeploymentRequest'", field);
    }
}

const char *VnfDeploymentRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VnfDeploymentRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: return oppstring2string(pp->getVnfName());
        case FIELD_vnfType: return enum2string(pp->getVnfType(), "VnfType");
        case FIELD_requestId: return long2string(pp->getRequestId());
        case FIELD_cpuRequest: return double2string(pp->getCpuRequest());
        case FIELD_memoryRequest: return double2string(pp->getMemoryRequest());
        case FIELD_bandwidthRequest: return double2string(pp->getBandwidthRequest());
        case FIELD_vnfIpAddress: return long2string(pp->getVnfIpAddress());
        case FIELD_firewallLbVip: return long2string(pp->getFirewallLbVip());
        case FIELD_backendServerIps: return long2string(pp->getBackendServerIps(i));
        default: return "";
    }
}

void VnfDeploymentRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: pp->setVnfName((value)); break;
        case FIELD_requestId: pp->setRequestId(string2long(value)); break;
        case FIELD_cpuRequest: pp->setCpuRequest(string2double(value)); break;
        case FIELD_memoryRequest: pp->setMemoryRequest(string2double(value)); break;
        case FIELD_bandwidthRequest: pp->setBandwidthRequest(string2double(value)); break;
        case FIELD_vnfIpAddress: pp->setVnfIpAddress(string2long(value)); break;
        case FIELD_firewallLbVip: pp->setFirewallLbVip(string2long(value)); break;
        case FIELD_backendServerIps: pp->setBackendServerIps(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentRequest'", field);
    }
}

omnetpp::cValue VnfDeploymentRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: return pp->getVnfName();
        case FIELD_vnfType: return static_cast<int>(pp->getVnfType());
        case FIELD_requestId: return pp->getRequestId();
        case FIELD_cpuRequest: return pp->getCpuRequest();
        case FIELD_memoryRequest: return pp->getMemoryRequest();
        case FIELD_bandwidthRequest: return pp->getBandwidthRequest();
        case FIELD_vnfIpAddress: return pp->getVnfIpAddress();
        case FIELD_firewallLbVip: return pp->getFirewallLbVip();
        case FIELD_backendServerIps: return pp->getBackendServerIps(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VnfDeploymentRequest' as cValue -- field index out of range?", field);
    }
}

void VnfDeploymentRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: pp->setVnfName(value.stringValue()); break;
        case FIELD_requestId: pp->setRequestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_cpuRequest: pp->setCpuRequest(value.doubleValue()); break;
        case FIELD_memoryRequest: pp->setMemoryRequest(value.doubleValue()); break;
        case FIELD_bandwidthRequest: pp->setBandwidthRequest(value.doubleValue()); break;
        case FIELD_vnfIpAddress: pp->setVnfIpAddress(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_firewallLbVip: pp->setFirewallLbVip(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_backendServerIps: pp->setBackendServerIps(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentRequest'", field);
    }
}

const char *VnfDeploymentRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr VnfDeploymentRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VnfDeploymentRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentRequest *pp = omnetpp::fromAnyPtr<VnfDeploymentRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentRequest'", field);
    }
}

Register_Class(VnfDeploymentResponse)

VnfDeploymentResponse::VnfDeploymentResponse(const char *name, short kind) : ::NfvMessage(name, kind)
{
}

VnfDeploymentResponse::VnfDeploymentResponse(const VnfDeploymentResponse& other) : ::NfvMessage(other)
{
    copy(other);
}

VnfDeploymentResponse::~VnfDeploymentResponse()
{
}

VnfDeploymentResponse& VnfDeploymentResponse::operator=(const VnfDeploymentResponse& other)
{
    if (this == &other) return *this;
    ::NfvMessage::operator=(other);
    copy(other);
    return *this;
}

void VnfDeploymentResponse::copy(const VnfDeploymentResponse& other)
{
    this->requestId = other.requestId;
    this->success = other.success;
    this->vnfName = other.vnfName;
    this->infoMessage = other.infoMessage;
    this->deployedVnfIp = other.deployedVnfIp;
}

void VnfDeploymentResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::NfvMessage::parsimPack(b);
    doParsimPacking(b,this->requestId);
    doParsimPacking(b,this->success);
    doParsimPacking(b,this->vnfName);
    doParsimPacking(b,this->infoMessage);
    doParsimPacking(b,this->deployedVnfIp);
}

void VnfDeploymentResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::NfvMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->requestId);
    doParsimUnpacking(b,this->success);
    doParsimUnpacking(b,this->vnfName);
    doParsimUnpacking(b,this->infoMessage);
    doParsimUnpacking(b,this->deployedVnfIp);
}

int VnfDeploymentResponse::getRequestId() const
{
    return this->requestId;
}

void VnfDeploymentResponse::setRequestId(int requestId)
{
    this->requestId = requestId;
}

bool VnfDeploymentResponse::getSuccess() const
{
    return this->success;
}

void VnfDeploymentResponse::setSuccess(bool success)
{
    this->success = success;
}

const char * VnfDeploymentResponse::getVnfName() const
{
    return this->vnfName.c_str();
}

void VnfDeploymentResponse::setVnfName(const char * vnfName)
{
    this->vnfName = vnfName;
}

const char * VnfDeploymentResponse::getInfoMessage() const
{
    return this->infoMessage.c_str();
}

void VnfDeploymentResponse::setInfoMessage(const char * infoMessage)
{
    this->infoMessage = infoMessage;
}

int VnfDeploymentResponse::getDeployedVnfIp() const
{
    return this->deployedVnfIp;
}

void VnfDeploymentResponse::setDeployedVnfIp(int deployedVnfIp)
{
    this->deployedVnfIp = deployedVnfIp;
}

class VnfDeploymentResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestId,
        FIELD_success,
        FIELD_vnfName,
        FIELD_infoMessage,
        FIELD_deployedVnfIp,
    };
  public:
    VnfDeploymentResponseDescriptor();
    virtual ~VnfDeploymentResponseDescriptor();

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

Register_ClassDescriptor(VnfDeploymentResponseDescriptor)

VnfDeploymentResponseDescriptor::VnfDeploymentResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VnfDeploymentResponse)), "NfvMessage")
{
    propertyNames = nullptr;
}

VnfDeploymentResponseDescriptor::~VnfDeploymentResponseDescriptor()
{
    delete[] propertyNames;
}

bool VnfDeploymentResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VnfDeploymentResponse *>(obj)!=nullptr;
}

const char **VnfDeploymentResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VnfDeploymentResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VnfDeploymentResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int VnfDeploymentResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestId
        FD_ISEDITABLE,    // FIELD_success
        FD_ISEDITABLE,    // FIELD_vnfName
        FD_ISEDITABLE,    // FIELD_infoMessage
        FD_ISEDITABLE,    // FIELD_deployedVnfIp
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *VnfDeploymentResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestId",
        "success",
        "vnfName",
        "infoMessage",
        "deployedVnfIp",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int VnfDeploymentResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "success") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "vnfName") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "infoMessage") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "deployedVnfIp") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *VnfDeploymentResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_requestId
        "bool",    // FIELD_success
        "string",    // FIELD_vnfName
        "string",    // FIELD_infoMessage
        "int",    // FIELD_deployedVnfIp
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **VnfDeploymentResponseDescriptor::getFieldPropertyNames(int field) const
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

const char *VnfDeploymentResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int VnfDeploymentResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VnfDeploymentResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VnfDeploymentResponse'", field);
    }
}

const char *VnfDeploymentResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VnfDeploymentResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        case FIELD_requestId: return long2string(pp->getRequestId());
        case FIELD_success: return bool2string(pp->getSuccess());
        case FIELD_vnfName: return oppstring2string(pp->getVnfName());
        case FIELD_infoMessage: return oppstring2string(pp->getInfoMessage());
        case FIELD_deployedVnfIp: return long2string(pp->getDeployedVnfIp());
        default: return "";
    }
}

void VnfDeploymentResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        case FIELD_requestId: pp->setRequestId(string2long(value)); break;
        case FIELD_success: pp->setSuccess(string2bool(value)); break;
        case FIELD_vnfName: pp->setVnfName((value)); break;
        case FIELD_infoMessage: pp->setInfoMessage((value)); break;
        case FIELD_deployedVnfIp: pp->setDeployedVnfIp(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentResponse'", field);
    }
}

omnetpp::cValue VnfDeploymentResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        case FIELD_requestId: return pp->getRequestId();
        case FIELD_success: return pp->getSuccess();
        case FIELD_vnfName: return pp->getVnfName();
        case FIELD_infoMessage: return pp->getInfoMessage();
        case FIELD_deployedVnfIp: return pp->getDeployedVnfIp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VnfDeploymentResponse' as cValue -- field index out of range?", field);
    }
}

void VnfDeploymentResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        case FIELD_requestId: pp->setRequestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_success: pp->setSuccess(value.boolValue()); break;
        case FIELD_vnfName: pp->setVnfName(value.stringValue()); break;
        case FIELD_infoMessage: pp->setInfoMessage(value.stringValue()); break;
        case FIELD_deployedVnfIp: pp->setDeployedVnfIp(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentResponse'", field);
    }
}

const char *VnfDeploymentResponseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr VnfDeploymentResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VnfDeploymentResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentResponse *pp = omnetpp::fromAnyPtr<VnfDeploymentResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentResponse'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

