//
//  DKQuery.h
//  DataKit
//
//  Created by Erik Aigner on 23.02.12.
//  Copyright (c) 2012 chocomoko.com. All rights reserved.
//

#import "DKConstants.h"


@class DKEntity;
@class DKMapReduce;

typedef void (^DKQueryResultBlock)(DKEntity *entity, NSError *error);
typedef void (^DKQueryResultsBlock)(NSArray *results, NSError *error);
typedef void (^DKQueryResultCountBlock)(NSUInteger count, NSError *error);

/**
 Class for performing queries on entity collections.
 */
@interface DKQuery : NSObject

/** @name Options */

/**
 The entity name to perform the query on
 */
@property (nonatomic, copy, readonly) NSString *entityName;

/**
 Limit number of returned results
 */
@property (nonatomic, assign) NSUInteger limit;

/**
 Number of results to skip. Will be ignored if map reduce is set.
 */
@property (nonatomic, assign) NSUInteger skip;

/**
 The map reduce to perform on the query.
 */
@property (nonatomic, strong) DKMapReduce *mapReduce;

/**
 The cache policy to use for the query.
 */
@property (nonatomic, assign) DKCachePolicy cachePolicy;

/** @name Creating and Initializing Queries */

/**
 Creates a new query for the given entity name
 @param entityName The name of the entity to query
 @return The initialized query
 */
+ (DKQuery *)queryWithEntityName:(NSString *)entityName;

/**
 Initializes a new query for the given entity name
 @param entityName The name of the entity to fetch.
 @return The initialized query
 */
- (id)initWithEntityName:(NSString *)entityName;

/** @name Logical Operations */

/**
 Add an OR condition to the query using the proxy object
 @return or The OR proxy object.
 */
- (DKQuery *)or;

/**
 Add an AND condition using the proxy object
 @return and The AND proxy object.
 */
- (DKQuery *)and;

/** @name Ordering */

/**
 Sorts the query in ascending order by key
 @param key The sort key
 */
- (void)orderAscendingByKey:(NSString *)key;

/**
 Sorts the query in descending order by key
 @param key The sort key
 */
- (void)orderDescendingByKey:(NSString *)key;

/** @name Conditions */

/**
 Adds an equal condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key equalTo:(id)object;

/**
 Adds a less-than condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key lessThan:(id)object;

/**
 Adds a less-than-or-equal condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key lessThanOrEqualTo:(id)object;

/*!
 Adds a greater-than condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key greaterThan:(id)object;

/**
 Adds a greater-than-or-equal condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key greaterThanOrEqualTo:(id)object;

/**
 Adds an not-equal condition to the query
 @param key The entity key
 @param object The condition object
 */
- (void)whereKey:(NSString *)key notEqualTo:(id)object;

/**
 Adds an contained-in condition to the query
 @param key The entity key
 @param array The objects to check
 @discussion The key value must be contained in the given array.
 */
- (void)whereKey:(NSString *)key containedIn:(NSArray *)array;

/**
 Adds an not-contained-in condition to the query
 @param key The entity key
 @param array The objects to check
 @discussion The key value must not be contained in the given array
 */
- (void)whereKey:(NSString *)key notContainedIn:(NSArray *)array;

/**
 Adds an contains-all condition to the query
 @param key The entity key
 @param array The objects to check
 @discussion The key value must contain all values in the given array
 */
- (void)whereKey:(NSString *)key containsAllIn:(NSArray *)array;

/**
 Matches the regex with no options set
 @param key The entity key
 @param regex The regex to match
 @see <whereKey:matchesRegex:options:>
 */
- (void)whereKey:(NSString *)key matchesRegex:(NSString *)regex;

/**
 Matches the regex using the provided option mask
 @param key The entity key
 @param regex The regex to match
 @param options The regex options
 */
- (void)whereKey:(NSString *)key matchesRegex:(NSString *)regex options:(DKRegexOption)options;

/**
 Checks if the object for key contains the string
 @param key The entity key
 @param string The string to match
 */
- (void)whereKey:(NSString *)key containsString:(NSString *)string;

/**
 Checks if the object for key has the given prefix
 @param key The entity key
 @param prefix The prefix string to match
 */
- (void)whereKey:(NSString *)key hasPrefix:(NSString *)prefix;

/**
 Checks if the object for key has the given suffix
 @param key The entity key
 @param suffix The suffix string to match
 */
- (void)whereKey:(NSString *)key hasSuffix:(NSString *)suffix;

/**
 Checks if the entity key exists
 @param key The entity key
 */
- (void)whereKeyExists:(NSString *)key;

/**
 Checks if the entity key does not exist
 @param key The entity key
 */
- (void)whereKeyDoesNotExist:(NSString *)key;

- (void)includeKey:(NSString *)key UNAVAILABLE_ATTRIBUTE; // UNIMPLEMENTED

/** @name Executing Queries */

/**
 Finds all matching entities
 @return The matching entities
 */
- (NSArray *)findAll;

/**
 Finds all matching entities
 @param error The error object to set on error
 @return The matching entities
 */
- (NSArray *)findAll:(NSError **)error;

/**
 Finds all matching entities in the background and returns them to the callback block
 @param block The result callback
 */
- (void)findAllInBackgroundWithBlock:(DKQueryResultsBlock)block;

/**
 Finds the first matching entity
 @return The matched entity
 @exception NSInternalInconsistencyException Raises an exception if a map reduce is set
 */
- (DKEntity *)findOne;

/**
 Finds the first matching entity
 @param error The error object written on error
 @return The matched entity
 @exception NSInternalInconsistencyException Raises an exception if a map reduce is set
 */
- (DKEntity *)findOne:(NSError **)error;

/**
 Finds the first matching entity in the background and returns it to the callback block
 @param block The result callback block
 @exception NSInternalInconsistencyException Raises an exception if a map reduce is set
 */
- (void)findOneInBackgroundWithBlock:(DKQueryResultBlock)block;

/**
 Finds an entity by it's unique ID
 @param entityId The entity ID to find
 @return Returns the entity with the matching ID
 */
- (DKEntity *)findById:(NSString *)entityId;

/**
 Finds an entity by it's unique ID
 @param entityId The entity ID to find
 @param error The error object that is written on error
 @return The entity with the matching ID
 */
- (DKEntity *)findById:(NSString *)entityId error:(NSError **)error;

/**
 Finds an entity by it's unique ID in the background and returns it to the callback block
 @param entityId The entity ID to find
 @param block The result callback block
 */
- (void)findById:(NSString *)entityId inBackgroundWithBlock:(DKQueryResultBlock)block;

/** @name Aggregation */

/**
 Counts the entities matching the query
 @return The matched entity count
 */
- (NSInteger)countAll;

/**
 Counts the entities matching the query
 @param error The error object that is written on error
 @return The matched entity count
 */
- (NSInteger)countAll:(NSError **)error;

/**
 Counts the entities matching the query in the background and returns the result to the block
 @param block The result callback block
 */
- (void)countAllInBackgroundWithBlock:(DKQueryResultCountBlock)block;

/** @name Resetting Conditions */

/**
 Resets all query conditions
 */
- (void)reset;

+ (id)new UNAVAILABLE_ATTRIBUTE;
- (id)init UNAVAILABLE_ATTRIBUTE;

@end
