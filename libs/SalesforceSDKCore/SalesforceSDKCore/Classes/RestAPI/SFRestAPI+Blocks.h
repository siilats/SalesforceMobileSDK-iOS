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

#import <Foundation/Foundation.h>
#import <SalesforceSDKCore/SFRestAPI.h>

NS_ASSUME_NONNULL_BEGIN
@class SFSDKCompositeResponse;
@class SFSDKBatchResponse;
@class SFSDKCompositeRequest;
@class SFSDKBatchRequest;

@interface SFRestAPI (Blocks) <SFRestRequestDelegate>

// Block types
typedef void (^SFRestRequestFailBlock) (id _Nullable response, NSError * _Nullable e, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestRequestFailBlock);
typedef void (^SFRestDictionaryResponseBlock) (NSDictionary * _Nullable dict, NSURLResponse * _Nullable rawResponse)  NS_SWIFT_NAME(RestDictionaryResponseBlock);
typedef void (^SFRestArrayResponseBlock) (NSArray * _Nullable arr, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestArrayResponseBlock);
typedef void (^SFRestDataResponseBlock) (NSData* _Nullable data, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestDataResponseBlock);
typedef void (^SFRestResponseBlock) (id _Nullable response, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestResponseBlock);
typedef void (^SFRestCompositeResponseBlock) (SFSDKCompositeResponse *response, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestCompositeResponseBlock);
typedef void (^SFRestBatchResponseBlock) (SFSDKBatchResponse *response, NSURLResponse * _Nullable rawResponse) NS_SWIFT_NAME(RestBatchResponseBlock);

/** Creates an error object with the given description.
 @param description Description
 */
+ (NSError *)errorWithDescription:(NSString *)description;

/**
 * Sends a request you've already built, using blocks to return status.
 *
 * @param request SFRestRequest to be sent.
 * @param failureBlock Block to be executed when the request fails (timeout, cancel, or error).
 * @param successBlock Block to be executed when the request successfully completes.
 */
- (void) sendRequest:(SFRestRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestResponseBlock)successBlock NS_REFINED_FOR_SWIFT;

/**
 * Sends a request you've already built, using blocks to return status.
 *
 * @param request Composite request to be sent.
 * @param failureBlock Block to be executed when the request fails (timeout, cancel, or error).
 * @param successBlock Block to be executed when the request successfully completes.
 */
- (void) sendCompositeRequest:(SFSDKCompositeRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestCompositeResponseBlock)successBlock NS_REFINED_FOR_SWIFT;

/**
 * Sends a request you've already built, using blocks to return status.
 *
 * @param request Batch request to be sent.
 * @param failureBlock Block to be executed when the request fails (timeout, cancel, or error).
 * @param successBlock Block to be executed when the request successfully completes.
 */
- (void) sendBatchRequest:(SFSDKBatchRequest *)request failureBlock:(SFRestRequestFailBlock)failureBlock successBlock:(SFRestBatchResponseBlock)successBlock NS_REFINED_FOR_SWIFT;

/**
 * Executes a SOQL query.
 * @param query the SOQL query to be executed
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performSOQLQuery:(NSString *)query
                           failBlock:(SFRestFailBlock)failBlock
                       completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a SOQL query that returns the deleted objects.
 * @param query the SOQL query to be executed
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performSOQLQueryAll:(NSString *)query
                              failBlock:(SFRestFailBlock)failBlock
                          completeBlock:(SFRestDictionaryResponseBlock)completeBlock
                          NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a SOSL search.
 * @param search the SOSL search to be executed
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performSOSLSearch:(NSString *)search
                            failBlock:(SFRestFailBlock)failBlock
                        completeBlock:(SFRestDictionaryResponseBlock)completeBlock
                         NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a global describe.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performDescribeGlobalWithFailBlock:(SFRestFailBlock)failBlock
                                         completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a describe on a single sObject.
 * @param objectType the API name of the object to describe.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performDescribeWithObjectType:(NSString *)objectType
                                        failBlock:(SFRestFailBlock)failBlock
                                    completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Returns an `SFRestRequest` object that provides layout data for the specified parameters.
 * @param objectAPIName Object API name.
 * @param formFactor Form factor. Could be "Large", "Medium" or "Small". Default value is "Large".
 * @param layoutType Layout type. Could be "Compact" or "Full". Default value is "Full".
 * @param mode Mode. Could be "Create", "Edit" or "View". Default value is "View".
 * @param recordTypeId Record type ID. Default will be used if not supplied.
 * @param failBlock Failure block.
 * @param completeBlock Completion block.
 * @see https://developer.salesforce.com/docs/atlas.en-us.uiapi.meta/uiapi/ui_api_resources_record_layout.htm
 */
- (SFRestRequest *) performLayoutWithObjectAPIName:(NSString *)objectAPIName
                                        formFactor:(NSString *)formFactor
                                        layoutType:(NSString *)layoutType
                                              mode:(NSString *)mode
                                      recordTypeId:(NSString *)recordTypeId
                                         failBlock:(SFRestFailBlock)failBlock
                                     completeBlock:(SFRestDictionaryResponseBlock)completeBlock
                                        NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

- (SFRestRequest *) performPicklistWithObjectAPIName:(NSString *)objectAPIName
                                        formFactor:(NSString *)formFactor
                                        layoutType:(NSString *)layoutType
                                              mode:(NSString *)mode
                                      recordTypeId:(NSString *)recordTypeId
                                         failBlock:(SFRestFailBlock)failBlock
                                     completeBlock:(SFRestDictionaryResponseBlock)completeBlock
                                        NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.");;

/**
/**
 * Executes a metadata describe on a single sObject.
 * @param objectType the API name of the object to describe.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performMetadataWithObjectType:(NSString *)objectType
                                        failBlock:(SFRestFailBlock)failBlock
                                    completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a retrieve for a single record.
 * @param objectType the API name of the object to retrieve
 * @param objectId the record ID of the record to retrieve
 * @param fieldList an array of fields on this record to retrieve
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRetrieveWithObjectType:(NSString *)objectType
                                         objectId:(NSString *)objectId
                                        fieldList:(NSArray<NSString*> *)fieldList
                                        failBlock:(SFRestFailBlock)failBlock
                                    completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a DML update for a single record.
 * @param objectType the API name of the object to update
 * @param objectId the record ID of the object
 * @param fields a dictionary of fields to update.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performUpdateWithObjectType:(NSString *)objectType
                                       objectId:(NSString *)objectId
                                         fields:(NSDictionary<NSString*, id> *)fields
                                      failBlock:(SFRestFailBlock)failBlock
                                  completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a DML upsert for a single record.
 * @param objectType the API name of the object to update
 * @param externalIdField the API name of the external ID field to use for updating
 * @param externalId the actual external Id
 * @param fields a dictionary of fields to include in the upsert
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performUpsertWithObjectType:(NSString *)objectType
                                externalIdField:(NSString *)externalIdField
                                     externalId:(NSString *)externalId
                                         fields:(NSDictionary<NSString*, id> *)fields
                                      failBlock:(SFRestFailBlock)failBlock
                                  completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a DML delete on a single record
 * @param objectType the API name of the object to delete
 * @param objectId the actual Id of the record to delete
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performDeleteWithObjectType:(NSString *)objectType
                                       objectId:(NSString *)objectId
                                      failBlock:(SFRestFailBlock)failBlock
                                  completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a DML insert.
 * @param objectType the API name of the object to insert
 * @param fields a dictionary of fields to use in the insert.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performCreateWithObjectType:(NSString *)objectType
                                         fields:(NSDictionary<NSString*, id> *)fields
                                      failBlock:(SFRestFailBlock)failBlock
                                  completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a request to list REST API resources
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRequestForResourcesWithFailBlock:(SFRestFailBlock)failBlock
                                              completeBlock:(SFRestDictionaryResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a request to list REST API versions
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRequestForVersionsWithFailBlock:(SFRestFailBlock)failBlock
                                             completeBlock:(SFRestArrayResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a request to get a file rendition
 * @param sfdcId The Id of the file
 * @param version if nil fetches the most recent version, otherwise fetches this specific version
 * @param renditionType What format of rendition do you want to get
 * @param page which page to fetch, pages start at 0.
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRequestForFileRendition:(NSString *)sfdcId
                                           version:(NSString *)version
                                     renditionType:(NSString *)renditionType
                                              page:(NSUInteger)page
                                         failBlock:(SFRestFailBlock)failBlock
                                     completeBlock:(SFRestDataResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a request to get search scope and order
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRequestForSearchScopeAndOrderWithFailBlock:(SFRestFailBlock)failBlock
                                     completeBlock:(SFRestArrayResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");

/**
 * Executes a request to get search result layout
 * @param objectList comma-separated list of objects for which
 *               to return values; for example, "Account,Contact".
 * @param failBlock the block to be executed when the request fails (timeout, cancel, or error)
 * @param completeBlock the block to be executed when the request successfully completes
 * @return the newly sent SFRestRequest
 */
- (SFRestRequest *) performRequestForSearchResultLayout:(NSString*)objectList
                                              failBlock:(SFRestFailBlock)failBlock
                                          completeBlock:(SFRestArrayResponseBlock)completeBlock NS_SWIFT_UNAVAILABLE("Use RestRequest factory methods to construct the request and RestClient send instead.") SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use RestRequest factory methods to construct the request and RestClient send instead.");
@end

NS_ASSUME_NONNULL_END
