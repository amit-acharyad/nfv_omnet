//
// Generated file, do not edit! Created by opp_msgtool 6.1 from messages/deploymentplan.msg.
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
#include "deploymentplan_m.h"

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

Register_Class(VnfBlueprint)

VnfBlueprint::VnfBlueprint(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

VnfBlueprint::VnfBlueprint(const VnfBlueprint& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

VnfBlueprint::~VnfBlueprint()
{
}

VnfBlueprint& VnfBlueprint::operator=(const VnfBlueprint& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VnfBlueprint::copy(const VnfBlueprint& other)
{
    this->vnfName = other.vnfName;
    this->vnfType = other.vnfType;
    this->cpu = other.cpu;
    this->memory = other.memory;
    this->bandwidth = other.bandwidth;
}

void VnfBlueprint::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->vnfName);
    doParsimPacking(b,this->vnfType);
    doParsimPacking(b,this->cpu);
    doParsimPacking(b,this->memory);
    doParsimPacking(b,this->bandwidth);
}

void VnfBlueprint::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->vnfName);
    doParsimUnpacking(b,this->vnfType);
    doParsimUnpacking(b,this->cpu);
    doParsimUnpacking(b,this->memory);
    doParsimUnpacking(b,this->bandwidth);
}

const char * VnfBlueprint::getVnfName() const
{
    return this->vnfName.c_str();
}

void VnfBlueprint::setVnfName(const char * vnfName)
{
    this->vnfName = vnfName;
}

VnfType VnfBlueprint::getVnfType() const
{
    return this->vnfType;
}

void VnfBlueprint::setVnfType(VnfType vnfType)
{
    this->vnfType = vnfType;
}

double VnfBlueprint::getCpu() const
{
    return this->cpu;
}

void VnfBlueprint::setCpu(double cpu)
{
    this->cpu = cpu;
}

double VnfBlueprint::getMemory() const
{
    return this->memory;
}

void VnfBlueprint::setMemory(double memory)
{
    this->memory = memory;
}

double VnfBlueprint::getBandwidth() const
{
    return this->bandwidth;
}

void VnfBlueprint::setBandwidth(double bandwidth)
{
    this->bandwidth = bandwidth;
}

class VnfBlueprintDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vnfName,
        FIELD_vnfType,
        FIELD_cpu,
        FIELD_memory,
        FIELD_bandwidth,
    };
  public:
    VnfBlueprintDescriptor();
    virtual ~VnfBlueprintDescriptor();

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

Register_ClassDescriptor(VnfBlueprintDescriptor)

VnfBlueprintDescriptor::VnfBlueprintDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VnfBlueprint)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

VnfBlueprintDescriptor::~VnfBlueprintDescriptor()
{
    delete[] propertyNames;
}

bool VnfBlueprintDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VnfBlueprint *>(obj)!=nullptr;
}

const char **VnfBlueprintDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VnfBlueprintDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VnfBlueprintDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int VnfBlueprintDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,    // FIELD_cpu
        FD_ISEDITABLE,    // FIELD_memory
        FD_ISEDITABLE,    // FIELD_bandwidth
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *VnfBlueprintDescriptor::getFieldName(int field) const
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
        "cpu",
        "memory",
        "bandwidth",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int VnfBlueprintDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vnfName") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "vnfType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "cpu") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "memory") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *VnfBlueprintDescriptor::getFieldTypeString(int field) const
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
        "double",    // FIELD_cpu
        "double",    // FIELD_memory
        "double",    // FIELD_bandwidth
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **VnfBlueprintDescriptor::getFieldPropertyNames(int field) const
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

const char *VnfBlueprintDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int VnfBlueprintDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VnfBlueprintDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VnfBlueprint'", field);
    }
}

const char *VnfBlueprintDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VnfBlueprintDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: return oppstring2string(pp->getVnfName());
        case FIELD_vnfType: return enum2string(pp->getVnfType(), "VnfType");
        case FIELD_cpu: return double2string(pp->getCpu());
        case FIELD_memory: return double2string(pp->getMemory());
        case FIELD_bandwidth: return double2string(pp->getBandwidth());
        default: return "";
    }
}

void VnfBlueprintDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: pp->setVnfName((value)); break;
        case FIELD_cpu: pp->setCpu(string2double(value)); break;
        case FIELD_memory: pp->setMemory(string2double(value)); break;
        case FIELD_bandwidth: pp->setBandwidth(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfBlueprint'", field);
    }
}

omnetpp::cValue VnfBlueprintDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: return pp->getVnfName();
        case FIELD_vnfType: return static_cast<int>(pp->getVnfType());
        case FIELD_cpu: return pp->getCpu();
        case FIELD_memory: return pp->getMemory();
        case FIELD_bandwidth: return pp->getBandwidth();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VnfBlueprint' as cValue -- field index out of range?", field);
    }
}

void VnfBlueprintDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        case FIELD_vnfName: pp->setVnfName(value.stringValue()); break;
        case FIELD_cpu: pp->setCpu(value.doubleValue()); break;
        case FIELD_memory: pp->setMemory(value.doubleValue()); break;
        case FIELD_bandwidth: pp->setBandwidth(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfBlueprint'", field);
    }
}

const char *VnfBlueprintDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr VnfBlueprintDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VnfBlueprintDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfBlueprint *pp = omnetpp::fromAnyPtr<VnfBlueprint>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfBlueprint'", field);
    }
}

Register_Class(VnfDeploymentPlan)

VnfDeploymentPlan::VnfDeploymentPlan(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

VnfDeploymentPlan::VnfDeploymentPlan(const VnfDeploymentPlan& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

VnfDeploymentPlan::~VnfDeploymentPlan()
{
    for (size_t i = 0; i < blueprints_arraysize; i++)
        drop(&this->blueprints[i]);
    delete [] this->blueprints;
}

VnfDeploymentPlan& VnfDeploymentPlan::operator=(const VnfDeploymentPlan& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VnfDeploymentPlan::copy(const VnfDeploymentPlan& other)
{
    this->enterpriseId = other.enterpriseId;
    this->nfviNodeId = other.nfviNodeId;
    for (size_t i = 0; i < blueprints_arraysize; i++)
        drop(&this->blueprints[i]);
    delete [] this->blueprints;
    this->blueprints = (other.blueprints_arraysize==0) ? nullptr : new VnfBlueprint[other.blueprints_arraysize];
    blueprints_arraysize = other.blueprints_arraysize;
    for (size_t i = 0; i < blueprints_arraysize; i++) {
        this->blueprints[i] = other.blueprints[i];
        this->blueprints[i].setName(other.blueprints[i].getName());
        take(&this->blueprints[i]);
    }
}

void VnfDeploymentPlan::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->enterpriseId);
    doParsimPacking(b,this->nfviNodeId);
    b->pack(blueprints_arraysize);
    doParsimArrayPacking(b,this->blueprints,blueprints_arraysize);
}

void VnfDeploymentPlan::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->enterpriseId);
    doParsimUnpacking(b,this->nfviNodeId);
    delete [] this->blueprints;
    b->unpack(blueprints_arraysize);
    if (blueprints_arraysize == 0) {
        this->blueprints = nullptr;
    } else {
        this->blueprints = new VnfBlueprint[blueprints_arraysize];
        doParsimArrayUnpacking(b,this->blueprints,blueprints_arraysize);
    }
}

int VnfDeploymentPlan::getEnterpriseId() const
{
    return this->enterpriseId;
}

void VnfDeploymentPlan::setEnterpriseId(int enterpriseId)
{
    this->enterpriseId = enterpriseId;
}

int VnfDeploymentPlan::getNfviNodeId() const
{
    return this->nfviNodeId;
}

void VnfDeploymentPlan::setNfviNodeId(int nfviNodeId)
{
    this->nfviNodeId = nfviNodeId;
}

size_t VnfDeploymentPlan::getBlueprintsArraySize() const
{
    return blueprints_arraysize;
}

const VnfBlueprint& VnfDeploymentPlan::getBlueprints(size_t k) const
{
    if (k >= blueprints_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)blueprints_arraysize, (unsigned long)k);
    return this->blueprints[k];
}

void VnfDeploymentPlan::setBlueprintsArraySize(size_t newSize)
{
    VnfBlueprint *blueprints2 = (newSize==0) ? nullptr : new VnfBlueprint[newSize];
    size_t minSize = blueprints_arraysize < newSize ? blueprints_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        blueprints2[i] = this->blueprints[i];
    for (size_t i = 0; i < blueprints_arraysize; i++)
        drop(&this->blueprints[i]);
    delete [] this->blueprints;
    this->blueprints = blueprints2;
    blueprints_arraysize = newSize;
    for (size_t i = 0; i < blueprints_arraysize; i++)
        take(&this->blueprints[i]);
}

void VnfDeploymentPlan::setBlueprints(size_t k, const VnfBlueprint& blueprints)
{
    if (k >= blueprints_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)blueprints_arraysize, (unsigned long)k);
    this->blueprints[k] = blueprints;
}

void VnfDeploymentPlan::insertBlueprints(size_t k, const VnfBlueprint& blueprints)
{
    if (k > blueprints_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)blueprints_arraysize, (unsigned long)k);
    size_t newSize = blueprints_arraysize + 1;
    VnfBlueprint *blueprints2 = new VnfBlueprint[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        blueprints2[i] = this->blueprints[i];
    blueprints2[k] = blueprints;
    for (i = k + 1; i < newSize; i++)
        blueprints2[i] = this->blueprints[i-1];
    for (size_t i = 0; i < blueprints_arraysize; i++)
        drop(&this->blueprints[i]);
    delete [] this->blueprints;
    this->blueprints = blueprints2;
    blueprints_arraysize = newSize;
    for (size_t i = 0; i < blueprints_arraysize; i++)
        take(&this->blueprints[i]);
}

void VnfDeploymentPlan::appendBlueprints(const VnfBlueprint& blueprints)
{
    insertBlueprints(blueprints_arraysize, blueprints);
}

void VnfDeploymentPlan::eraseBlueprints(size_t k)
{
    if (k >= blueprints_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)blueprints_arraysize, (unsigned long)k);
    size_t newSize = blueprints_arraysize - 1;
    VnfBlueprint *blueprints2 = (newSize == 0) ? nullptr : new VnfBlueprint[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        blueprints2[i] = this->blueprints[i];
    for (i = k; i < newSize; i++)
        blueprints2[i] = this->blueprints[i+1];
    for (size_t i = 0; i < blueprints_arraysize; i++)
        drop(&this->blueprints[i]);
    delete [] this->blueprints;
    this->blueprints = blueprints2;
    blueprints_arraysize = newSize;
    for (size_t i = 0; i < blueprints_arraysize; i++)
        take(&this->blueprints[i]);
}

class VnfDeploymentPlanDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_enterpriseId,
        FIELD_nfviNodeId,
        FIELD_blueprints,
    };
  public:
    VnfDeploymentPlanDescriptor();
    virtual ~VnfDeploymentPlanDescriptor();

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

Register_ClassDescriptor(VnfDeploymentPlanDescriptor)

VnfDeploymentPlanDescriptor::VnfDeploymentPlanDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VnfDeploymentPlan)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

VnfDeploymentPlanDescriptor::~VnfDeploymentPlanDescriptor()
{
    delete[] propertyNames;
}

bool VnfDeploymentPlanDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VnfDeploymentPlan *>(obj)!=nullptr;
}

const char **VnfDeploymentPlanDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VnfDeploymentPlanDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VnfDeploymentPlanDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int VnfDeploymentPlanDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISRESIZABLE,    // FIELD_blueprints
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *VnfDeploymentPlanDescriptor::getFieldName(int field) const
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
        "blueprints",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int VnfDeploymentPlanDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "enterpriseId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nfviNodeId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "blueprints") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *VnfDeploymentPlanDescriptor::getFieldTypeString(int field) const
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
        "VnfBlueprint",    // FIELD_blueprints
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **VnfDeploymentPlanDescriptor::getFieldPropertyNames(int field) const
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

const char *VnfDeploymentPlanDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int VnfDeploymentPlanDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_blueprints: return pp->getBlueprintsArraySize();
        default: return 0;
    }
}

void VnfDeploymentPlanDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_blueprints: pp->setBlueprintsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VnfDeploymentPlan'", field);
    }
}

const char *VnfDeploymentPlanDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VnfDeploymentPlanDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return long2string(pp->getEnterpriseId());
        case FIELD_nfviNodeId: return long2string(pp->getNfviNodeId());
        case FIELD_blueprints: return pp->getBlueprints(i).str();
        default: return "";
    }
}

void VnfDeploymentPlanDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(string2long(value)); break;
        case FIELD_nfviNodeId: pp->setNfviNodeId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentPlan'", field);
    }
}

omnetpp::cValue VnfDeploymentPlanDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: return pp->getEnterpriseId();
        case FIELD_nfviNodeId: return pp->getNfviNodeId();
        case FIELD_blueprints: return omnetpp::toAnyPtr(&pp->getBlueprints(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VnfDeploymentPlan' as cValue -- field index out of range?", field);
    }
}

void VnfDeploymentPlanDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_enterpriseId: pp->setEnterpriseId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_nfviNodeId: pp->setNfviNodeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentPlan'", field);
    }
}

const char *VnfDeploymentPlanDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_blueprints: return omnetpp::opp_typename(typeid(VnfBlueprint));
        default: return nullptr;
    };
}

omnetpp::any_ptr VnfDeploymentPlanDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        case FIELD_blueprints: return omnetpp::toAnyPtr(&pp->getBlueprints(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VnfDeploymentPlanDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VnfDeploymentPlan *pp = omnetpp::fromAnyPtr<VnfDeploymentPlan>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VnfDeploymentPlan'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

