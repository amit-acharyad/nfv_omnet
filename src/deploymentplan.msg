import vnftype;
packet VnfBlueprint {
    string vnfName;
    VnfType vnfType;
    double cpu;
    double memory;
    double bandwidth;
}

packet VnfDeploymentPlan {
    int enterpriseId;
    int nfviNodeId;
    VnfBlueprint blueprints[];  // array of VNF configs
}
