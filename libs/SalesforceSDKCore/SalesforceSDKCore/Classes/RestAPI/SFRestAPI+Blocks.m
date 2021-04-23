/* 
 * Copyright (c) 2011-present, salesforce.com, inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided 
 * that the following conditions are met:
 * 
 *    Redistributions of source code must retain the above copyright notice, this list of conditions and the 
 *    following disclaimer.
 *  
 *    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
 *    the following disclaimer in the documentation and/or other materials provided with the distribution. 
 *    
 *    Neither the name of salesforce.com, inc. nor the names of its contributors may be used to endorse or 
 *    promote products derived from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#import "SFRestAPI+Internal.h"
#import "SFRestAPI+Blocks.h"
#import "SFRestAPI+Files.h"
#import "SFSDKCompositeRequest.h"
#import "SFSDKBatchRequest.h"
#import "SFSDKBatchResponse+Internal.h"
#import "SFSDKCompositeResponse+Internal.h"
#import <objc/runtime.h>

// Pattern demonstrated in the Apple documentation. We use a static key
// whose address will be used by the objc_setAssociatedObject (no need to have a value).
static char FailureBlockKey;
static char SuccessBlockKey;

@implementation SFRestAPI (Blocks)

#pragma mark - error handling

+ (NSError *)errorWithDescription:(NSString *)description {    
    NSArray *objArray = @[description, @""];
    NSArray *keyArray = @[NSLocalizedDescriptionKey, NSFilePathErrorKey];
    NSDictionary *eDict = [NSDictionary dictionaryWithObjects:objArray
                                                      forKeys:keyArray];
    NSError *err = [[NSError alloc] initWithDomain:@"API Error"
                                              code:42 // life, the universe, and everything
                                          userInfo:eDict];
    return err;
}

#pragma mark - sending requests

- (void) sendRequest:(SFRestRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestResponseBlock)successBlock {
    objc_setAssociatedObject(request, &FailureBlockKey, failureBlock, OBJC_ASSOCIATION_COPY);
    objc_setAssociatedObject(request, &SuccessBlockKey, successBlock, OBJC_ASSOCIATION_COPY);
    [self send:request requestDelegate:self];
}

- (void) sendCompositeRequest:(SFSDKCompositeRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestCompositeResponseBlock)successBlock {
    [self sendRequest:request failureBlock:failureBlock successBlock:^(id response, NSURLResponse * rawResponse) {
        SFSDKCompositeResponse *compositeResponse = [[SFSDKCompositeResponse alloc] initWith:response];
        successBlock(compositeResponse, rawResponse);
    }];
}

- (void) sendBatchRequest:(SFSDKBatchRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestBatchResponseBlock)successBlock {
    [self sendRequest:request failureBlock:failureBlock successBlock:^(id response, NSURLResponse * rawResponse) {
        SFSDKBatchResponse *compositeResponse = [[SFSDKBatchResponse alloc] initWith:response];
        successBlock(compositeResponse, rawResponse);
    }];
}

#pragma mark - various request types

- (SFRestRequest *) performSOQLQuery:(NSString *)query failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForQuery:query apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performSOQLQueryAll:(NSString *)query failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForQueryAll:query apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performSOSLSearch:(NSString *)search failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForSearch:search apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performDescribeGlobalWithFailBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForDescribeGlobal:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performUpdateWithObjectType:(NSString *)objectType objectId:(NSString *)objectId fields:(NSDictionary *)fields failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForUpdateWithObjectType:objectType objectId:objectId fields:fields apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performUpsertWithObjectType:(NSString *)objectType externalIdField:(NSString *)externalIdField externalId:(NSString *)externalId fields:(NSDictionary *)fields failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForUpsertWithObjectType:objectType
                                                  externalIdField:externalIdField
                                                       externalId:externalId
                                                           fields:fields
                                                       apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performCreateWithObjectType:(NSString *)objectType fields:(NSDictionary *)fields failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForCreateWithObjectType:objectType fields:fields apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performDeleteWithObjectType:(NSString *)objectType objectId:(NSString *)objectId failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForDeleteWithObjectType:objectType objectId:objectId apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performDescribeWithObjectType:(NSString *)objectType failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForDescribeWithObjectType:objectType apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performLayoutWithObjectAPIName:(NSString *)objectAPIName formFactor:(NSString *)formFactor layoutType:(NSString *)layoutType mode:(NSString *)mode recordTypeId:(NSString *)recordTypeId failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForLayoutWithObjectAPIName:objectAPIName formFactor:formFactor layoutType:layoutType mode:mode recordTypeId:recordTypeId apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performPicklistWithObjectAPIName:(NSString *)objectAPIName formFactor:(NSString *)formFactor layoutType:(NSString *)layoutType mode:(NSString *)mode recordTypeId:(NSString *)recordTypeId failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForPicklistWithObjectAPIName:objectAPIName formFactor:formFactor layoutType:layoutType mode:mode recordTypeId:recordTypeId apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performMetadataWithObjectType:(NSString *)objectType failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForMetadataWithObjectType:objectType apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRetrieveWithObjectType:(NSString *)objectType objectId:(NSString *)objectId fieldList:(NSArray *)fieldList failBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    NSString *fields = fieldList ? [[[NSSet setWithArray:fieldList] allObjects] componentsJoinedByString:@","] : nil;
    SFRestRequest *request = [self requestForRetrieveWithObjectType:objectType objectId:objectId fieldList:fields apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRequestForResourcesWithFailBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestDictionaryResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForResources:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRequestForVersionsWithFailBlock:(SFRestFailBlock)failBlock completeBlock:(SFRestArrayResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForVersions];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRequestForFileRendition:(NSString *)sfdcId
                                           version:(NSString *)version
                                     renditionType:(NSString *)renditionType
                                              page:(NSUInteger)page
                                         failBlock:(SFRestFailBlock)failBlock
                                     completeBlock:(SFRestDataResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForFileRendition:sfdcId version:version renditionType:renditionType page:page apiVersion:self.apiVersion];
    [self sendRESTRequest:request
                failBlock:failBlock
            completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRequestForSearchScopeAndOrderWithFailBlock:(SFRestFailBlock)failBlock
                                           completeBlock:(SFRestArrayResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForSearchScopeAndOrder:self.apiVersion];
    [self sendRESTRequest:request failBlock:failBlock completeBlock:completeBlock];
    return request;
}

- (SFRestRequest *) performRequestForSearchResultLayout:(NSString *)objectList
                                              failBlock:(SFRestFailBlock)failBlock
                                          completeBlock:(SFRestArrayResponseBlock)completeBlock {
    SFRestRequest *request = [self requestForSearchResultLayout:objectList apiVersion:self.apiVersion];
    [self sendRESTRequest:request failBlock:failBlock completeBlock:completeBlock];
    return request;
}

#pragma mark - response delegate

- (void) triggerDelegatesForRequest:(SFRestRequest *)request success:(BOOL)success withObject:(id)object rawResponse:(NSURLResponse *)rawResponse error:(NSError *)error {
    if (success) {
        void (^successBlock)(id, NSURLResponse *);
        successBlock = (void (^) (id, NSURLResponse *))objc_getAssociatedObject(request, &SuccessBlockKey);
        if (successBlock) {
            successBlock(object, rawResponse);
        }
    } else {
        SFRestRequestFailBlock failBlock = (SFRestRequestFailBlock)objc_getAssociatedObject(request, &FailureBlockKey);
        if (failBlock) {
            failBlock(object, error, rawResponse);
        }
    }

    // Removes both blocks from the request.
    objc_setAssociatedObject(request, &FailureBlockKey, nil, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(request, &SuccessBlockKey, nil, OBJC_ASSOCIATION_ASSIGN);
}

- (void)request:(SFRestRequest *)request didSucceed:(id)dataResponse rawResponse:(NSURLResponse *)rawResponse {
    [self triggerDelegatesForRequest:request success:YES withObject:dataResponse rawResponse:rawResponse error:nil];
}

- (void)request:(SFRestRequest *)request didFail:(id)dataResponse rawResponse:(NSURLResponse *)rawResponse error:(NSError *)error {
    [self triggerDelegatesForRequest:request success:NO withObject:dataResponse rawResponse:rawResponse error:error];
}

@end
