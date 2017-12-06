//
//  FollowApps.h
//  FollowApps
//
//  Created by FollowApps on 07/05/12.
//  Copyright (c) 2012 FollowApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WatchConnectivity/WatchConnectivity.h>
#import <FollowApps/FAEmbeddedView.h>
#import <FollowApps/FAPush.h>
#import <FollowApps/FAInApp.h>
#import <FollowApps/FABadge.h>

#ifdef DEBUG
#define FADEBUG YES
#else
#define FADEBUG NO
#endif


@protocol FAFollowAppsDelegate;

@interface FAFollowApps : UIResponder

// _____________________________________________________
// ------------------- configuration -------------------

/*!
 Sets up the library which then handles automatically every device event: background entering, application closing, and so on.

 The developer doesn't have to do anything more than calling this line to get the library up and running for basic logging.

 If you want to send push notifications from FollowAnalytics, you need to ask the user to allow it, either by yourself or by calling `[FAFollowApps registerForPush]` after configuration.

 @param FAId Your FollowAnalytics API Key.
 @param appGroup the appGroup shared between app and extensions (this parameter optional is needed for the badge management)
 @param isDebug Always use FADEBUG so that the parameter is automatically set depending on your build configuration.
 @param options Pass the launchOptions you get from `application:didFinishLaunchingWithOptions`.
 */
+ (BOOL)configureWithId:(nonnull NSString *)FAId
         sharedAppGroup:(nullable NSString * )appGroup
             automatise:(BOOL)automatise
           debugStateOn:(BOOL)isDebug
                options:(nullable NSDictionary *)options;

/*!
 Call this method only if you have a watch extension and the FollowAnalytics Watch SDK
 */
+ (void)enableWatchWithFollow;


/*!
 Configure the campaign storage.
 @param push A bool to specify if push have to be formated as message.
 @param inApp A bool to specify if inApp have to be formated as message.
 */
+ (void)storeMessagesPush:(BOOL)push inApp:(BOOL)inApp;


/*!
 If you want FollowAnalytics to prompt the user to accept notifications, call this method. If you already get the authorization, no need to call this method.
 */
+ (void)registerForPush;

/*!
 If you want FollowAnalytics to prompt the user to accept the location, call this method.
 
 */
+ (void)enableGeoffencing;

/*!
 Changes the maximum duration spent in background within a session. Default is 120. After this delay, the session is considered over and a new one is started when the app goes back to foreground.
 
 For instance, leaving an app to sign in using the Facebook app for sharing shouldn't count as ending and starting a new session in terms of analytics.
 
 Should your app require specific background side usage by the user, this is the parameter you'd want to fine tune.
 
 @param duration allowed number of seconds outside of the app.
 */
+ (void)setMaxBackgroundTimeWithinSession:(NSTimeInterval)duration;

/*!
 Device ID generated by FollowAnalytics, used to uniquely identify a device
 */
+ (NSUUID * _Nonnull)deviceUUID;


/*!
 Original Application Delegate
 */

+ (id<UIApplicationDelegate>_Nonnull)applicationDelegate;


// _____________________________________________________
// ------------------ logging methods ------------------

/*!
 Logs an event with details associated.

 For instance, you could log that the user went to on a product view by calling `[FAFollowApps logEventWithName:@"Product View" details:@"Product name"];`. This way you would be able to see which products are seen the most.

 Try to use a limited number of event names. Also, remember that the event name you use with the SDK can be different from the one shown on the platform (see Analytics > Settings on the platform), and that groups of events can be created on the platform, therefore helping you to classify your various events.

 @param name The name of the event.
 @param details A string or dictionary giving context about the event you're logging.
 @return true for success, false if the log couldn't be saved.
 */
+ (BOOL)logEventWithName:(NSString *_Nonnull)name
				 details:(id _Nullable )details;

/*!
 Logs an error that occurred, with its name and some context/details.

 For instance, if you encounter an unexpected return value from your web service, you could call `[FAFollowApps logErrorWithName:@"Unexpected Webservice X value" details:@"the_value"]`.

 Like for events, the name displayed on the platform can be changed from there, et errors groups can be created.

 @param name The name of the error.
 @param details A string or dictionary giving context about the error you're logging.
 @return returns true for success, false if the log couldn't be saved.
 */
+ (BOOL)logErrorWithName:(NSString *_Nonnull)name
				 details:(id _Nullable)details;

/*!
 Lists installed SDKs that FollowAnalytics can fetch tags from.

 @return Array containing FASDK* constant strings (defined at the bottom of this file).
 */
+ (NSArray * _Nonnull)detectedSDKs;

/*!
 Declares the SDKs FollowAnalytics should fetch tags from.

 Tags fetched from a source will be prefixed by 2 or 3 chars identifying it.

 You can tell the SDK to fetch whatever it detects by calling `[FAFollowApps fetchTagsFromSDKs:[FAFollowApps detectedSDKs]]`
 
 @param Array containing FASDK* constant strings describing SDKs.
 */
+ (void)fetchTagsFromSDKs:(NSArray *_Nonnull)SDKKeys;

// _____________________________________________________
// ------- user knowledge and attributes methods -------


/*!
 @return The currently set user indentifier.
 */
+ (NSString *_Nullable)currentUserIdentifier;

/*!
 Resets the current user for all further attributes and behaviors logged.

 Doing so restarts a new session without an User Id information.
 */
+ (BOOL)unsetCurrentUserIdentifier;


#pragma mark - User Attributes
/*!
 Sets the user id. If called multiple times, the previous value will be overriden.
 
 @param userId String for the id of the user.
 */
+ (BOOL)setUserId:(NSString *_Nullable)userId;

/*!
 Sets the user first name. If called multiple times, the previous value will be overriden.
 If you want to remove the user first name, pass nil in parameter.
 
 @param firstName String for the first name of the user.
 */
+ (BOOL)setUserFirstName:(NSString *_Nullable)firstName;

/*!
 Sets the user last name. If called multiple times, the previous value will be overriden.
 If you want to remove the user last name, pass nil in parameter.

 @param lastName String for the last name of the user.
 */
+ (BOOL)setUserLastName:(NSString *_Nullable)lastName;

/*!
 Sets the user email. If called multiple times, the previous value will be overriden.
 If you want to remove the user email, pass nil in parameter.

 @param email String for the email of the user.
 */
+ (BOOL)setUserEmail:(NSString *_Nullable)email;

/*!
 Sets the user date of birth. If called multiple times, the previous value will be overriden.
 If you want to remove the user date of birth, pass nil in parameter.

 @param date of birth Date for the date of birth of the user.
 */
+ (BOOL)setUserDateBirth:(NSDate *_Nullable)dateBirth;


typedef NS_ENUM(NSInteger, FAGender) {
    FAGenderRemove      = 0,
    FAGenderMale        = 1,
    FAGenderFemale      = 2,
    FAGenderOther       = 3
};

/*!
 Sets the user gender. If called multiple times, the previous value will be overriden.
 If you want to remove the user gender, pass nil in parameter.

 @param gender String for the gender of the user.
 */
+ (BOOL)setUserGender:(FAGender)gender;

/*!
 Sets the user country. If called multiple times, the previous value will be overriden.
 If you want to remove the user country, pass nil in parameter.

 @param country String for the country of the user.
 */
+ (BOOL)setUserCountry:(NSString *_Nullable)country;

/*!
 Sets the user city. If called multiple times, the previous value will be overriden.
 If you want to remove the user city, pass nil in parameter.

 @param city String for the city of the user.
 */
+ (BOOL)setUserCity:(NSString *_Nullable)city;

/*!
 Sets the user region. If called multiple times, the previous value will be overriden.
 If you want to remove the user region, pass nil in parameter.

 @param region String for the region of the user.
 */
+ (BOOL)setUserRegion:(NSString *_Nullable)region;

/*!
 Sets the user profile picture url. If called multiple times, the previous value will be overriden.
 If you want to remove the user profile picture, pass nil in parameter.

 @param url String for the profile picture url of the user.
 */
+ (BOOL)setUserProfilePictureUrl:(NSString *_Nullable)url;

typedef NS_ENUM(NSInteger, FADataType) {
    FADataTypeGeneric       = 0,
    FADataTypeDate          = 1,
    FADataTypeDateTime      = 2
};

/**
 *  Set a value of type integer for a custom User Attribute
 *
 *  @param intValue NSInteger value
 *  @param key      Custom attribute key
 */

+ (BOOL)setInt:(NSInteger)intValue forKey:(NSString *_Nonnull)key;

/**
 *  Set a value of type double for a custom User Attribute
 *
 *  @param doubleValue double value
 *  @param key         Custom attribute key
 */
+ (BOOL)setDouble:(double)doubleValue forKey:(NSString *_Nonnull)key;

/**
 *  Set a value of type boolean for a custom User Attribute
 *
 *  @param booleanValue boolean value
 *  @param key          Custom attribute key
 */
+ (BOOL)setBoolean:(BOOL)booleanValue forKey:(NSString *_Nonnull)key;

/**
 *  Set a value of type Date for a custom User Attribute
 *
 *  @param dateValue format: 'YYYY-MM-DD'
 *  @param key       Custom attribute key
 */
+ (BOOL)setDate:(NSDate *_Nonnull)dateValue forKey:(NSString *_Nonnull)key;

/**
 *  Set a value of type DateTime for a custom User Attribute
 *
 *  @param dateValue format
 *  @param key       Custom attribute key
 */
+ (BOOL)setDateTime:(NSDate *_Nonnull)dateValue forKey:(NSString *_Nonnull)key;

/**
 *  Set a value of type NSString for a custom User Attribute
 *
 *  @param stringValue format
 *  @param key       Custom attribute key
 */
+ (BOOL)setString:(NSString *_Nonnull)stringValue forKey:(NSString *_Nonnull)key;

/*!
 Defines an attribute regarding the user of the app: preference, habit, any attribute.
 Type accepted: NSString, NSDate
 The attributes are associated to the currently set user identifier, or to a default user until a first user indentifier is set, which will qualify this default user.
 
 @param key Key for the attribute you're setting.
 @param attribute id value you want to associate to that key.
 
 This method is deprecated and will be removed in a future release.
 Please use the corresponding method : setString, setBoolean, setInt, setDouble, setDate, setDateTime instead.
 @deprecated

 */
+ (void)addCustomUserAttribute:(id _Nonnull)attribute forKey:(NSString *_Nonnull)key withDataType:(FADataType)dataType __attribute((deprecated(("use setString, setBoolean, setInt, setDouble, setDate, setDateTime instead"))));


/*!
 Defines an attribute regarding the user of the app: preference, habit, any attribute.
 The attributes are associated to the currently set user identifier, or to a default user until a first user indentifier is set, which will qualify this default user.
 If you have only one attribute to add in a set, pass an NSset with one element.
 Type accepted: NSString
 
 @param key Key for the attribute you're setting.
 @param attribute Set value you want to associate to that key.
 @deprecated
 */
+ (void)addCustomUserAttributeSet:(NSSet *_Nonnull)attributeSet forKey:(NSString *_Nonnull)key __attribute((deprecated(("use addCustomUserAttribute:toSetWithKey: or addCustomuserAttributeSet:toSetWithKey"))));

/*!
 Remove a custom user attribute from a Set.
 Type accepted: NSString
 
 @param key Key for the attribute you're setting.
 @param attribute string value you want to remove to that key.
 @deprecated
 */
+ (void)removeCustomUserAttributeSet:(NSString *_Nonnull)attribute forKey:(NSString *_Nonnull)key __attribute((deprecated(("use removeCustomUserAttribute:fromSetWithKey:"))));


/*!
 Defines an attribute regarding the user of the app: preference, habit, any attribute.
 The attributes are associated to the currently set user identifier, or to a default user until a first user indentifier is set, which will qualify this default user.
 Add the attribute string to the specify set.
 If you have more than one attribute to add in a set, use addCustomuserAttributeSet:toSetWithKey
 @param key Key for the attribute you're setting.
 @param attribute string value you want to associate to that set of key.
 */

+ (BOOL)addCustomUserAttribute:(NSString *_Nonnull)attribute toSetWithKey:(NSString *_Nonnull)key;
/*!
 Defines an attribute regarding the user of the app: preference, habit, any attribute.
 The attributes are associated to the currently set user identifier, or to a default user until a first user indentifier is set, which will qualify this default user.
 If you have only one attribute to add in a set, use addCustomUserAttribute:toSetWithKey:
 Type accepted: NSString
 
 @param key Key for the attribute you're setting.
 @param attribute Set value you want to associate to that key.
 */

+ (BOOL)addCustomUserAttributeSet:(NSSet *_Nonnull)set toSetWithKey:(NSString *_Nonnull)key;


/*!
 Remove a custom user attribute from a Set.
 Type accepted: NSString
 
 @param key Key for the attribute you're setting.
 @param attribute string value you want to remove to that key.
 
 */

+ (BOOL)removeCustomUserAttribute:(NSString *_Nonnull)attribute fromSetWithkey:(NSString *_Nonnull)key;

/*!
 Remove a set of custom user attribute from a Set.
 Type accepted: NSString
 
 @param key Key for the attribute you're setting.
 @param set Set<NSSting *> you want to remove to that key.
 */

+ (BOOL)removeCustomUserAtributeSet:(NSSet *_Nonnull)set fromSetWithKey:(NSString *_Nonnull)key;

/*!
 Remove a custom user attribute.
 @param key Key for the attribute you're removing.
 */
+ (BOOL)removeCustomUserAttributeForKey:(NSString *_Nonnull)key;

/*!
 Delete a set of custom user attributes.
 
 @param key Key for the set attributes you're deleting.
 */
+ (BOOL)deleteCustomUserAttributeSetForKey:(NSString *_Nonnull)key;


// --------------------- Rich Campaigns ---------------------

/*!
 Use this method to pause Rich Campaign display. Used when you don't want InApp campaigns to be shown over the current screen.
 This method is deprecated, please use `pauseCampaignDisplay` instead.
 @deprecated
 */
+ (void)pauseRichCampaignDisplay __attribute__((deprecated));

/*!
 Use this method to resume Rich Campaign display. Used when you're able to display Rich Campaigns on current or upcoming screens.
 This method is deprecated, please use `resumeCampaign` instead.
 @deprecated
 */
+ (void)resumeRichCampaignDisplay __attribute__((deprecated));


/*!
 Use this method to pause Rich Campaign display. Used when you don't want InApp campaigns to be shown over the current screen.
 */
+ (void)pauseCampaignDisplay;

/*!
 Use this method to resume Rich Campaign display. Used when you're able to display Rich Campaigns on current or upcoming screens.
 */
+ (void)resumeCampaignDisplay;

/*!
 *  Use this method to fetch the custom parameters from the latest Push Notification message received by the system
 */
+ (NSDictionary *_Nonnull)lastPushCampaignParams;


// ---------------------- In App -----------------------------

/*!
 Use this method to pause Popup Campaign display. Used when you don't want InApp campaigns to be shown over the current screen.
 */
+ (void)pausePopupCampaignDisplay;

/*!
 Use this method to resume Popup Campaign display. Used when you're able to display popup Campaigns on current or upcoming screens.
 */
+ (void)resumePopupCampaignDisplay;

/*!
 Use this method to pause Banner Campaign display. Used when you don't want Banner campaigns to be shown over the current screen.
 */
+ (void)pauseBannerCampaignDisplay;

/*!
 Use this method to resume Banner Campaign display. Used when you're able to display Banner Campaigns on current or upcoming screens.
 */
+ (void)resumeBannerCampaignDisplay;


@property(nonatomic, strong) id  <FAFollowAppsDelegate> _Nullable followAppsDelegate;

+ (FAFollowApps * _Nonnull)sharedFA;


- (void)applicationDidBecomeActive:(UIApplication * _Nonnull)application;

- (void)applicationDidEnterBackground:(UIApplication * _Nonnull)application;

- (void)applicationWillEnterForeground:(UIApplication * _Nonnull)application;

- (void)applicationWillTerminate:(UIApplication * _Nonnull)application;

- (void)applicationDidReceiveMemoryWarning:(UIApplication * _Nonnull)application;

- (void)application:(UIApplication * _Nonnull)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData * _Nullable)deviceToken;

- (void)application:(UIApplication * _Nonnull)application didReceiveRemoteNotification:(NSDictionary * _Nonnull)userInfo;

- (void)userNotificationCenter:(UNUserNotificationCenter * _Nonnull)center didReceiveNotificationResponse:(UNNotificationResponse * _Nonnull)response withCompletionHandler:(void (^ _Nullable)())completionHandler;

- (void)userNotificationCenter:(UNUserNotificationCenter * _Nonnull)center willPresentNotification:(UNNotification * _Nonnull)notification withCompletionHandler:(void (^ _Nullable)(UNNotificationPresentationOptions))completionHandler;

- (void)application:(UIApplication * _Nonnull)application handleActionWithIdentifier:(NSString * _Nullable)identifier forRemoteNotification:(NSDictionary * _Nonnull)userInfo completionHandler:(void (^ _Nullable)())completionHandler;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
- (void)application:(UIApplication * _Nonnull)application handleActionWithIdentifier:(NSString * _Nullable)identifier forLocalNotification:(UILocalNotification * _Nonnull)notification completionHandler:(void (^ _Nullable)())completionHandler;
#pragma GCC diagnostic pop

- (BOOL)application:(UIApplication * _Nonnull)application handleOpenURL:(NSURL * _Nonnull)url;

- (BOOL)application:(UIApplication * _Nonnull)application openURL:(NSURL * _Nonnull)url sourceApplication:(NSString * _Nullable)sourceApplication annotation:(id _Nullable)annotation;

- (BOOL)application:(UIApplication * _Nonnull)app openURL:(NSURL * _Nonnull)url options:(NSDictionary<id,id> * _Nullable)options;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
- (void)application:(UIApplication * _Nonnull)application didReceiveLocalNotification:(UILocalNotification * _Nonnull)notification;
#pragma GCC diagnostic pop

- (void)application:(UIApplication * _Nonnull)application performFetchWithCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

- (void)application:(UIApplication * _Nonnull)application didReceiveRemoteNotification:(NSDictionary * _Nonnull)userInfo fetchCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

- (void)application:(UIApplication * _Nonnull)application handleEventsForBackgroundURLSession:(NSString * _Nonnull)identifier completionHandler:(void (^ _Nullable)())completionHandler;

- (void)session:(WCSession * _Nonnull)session didReceiveMessage:(NSDictionary<NSString *,id> * _Nonnull)message replyHandler:(void (^ _Nullable)(NSDictionary<NSString *,id> * _Nonnull))replyHandler;


@end


// _____________________________________________________
// --------------- FAFollowApps Delegate ---------------

/*!
 Delegate to receive data and events from FollowAnalytics.
 
 @warning The delegate has to be your AppDelegate. Add the protocol on your appDelegate interface.
 */
@protocol FAFollowAppsDelegate <UIApplicationDelegate>

@optional

/*!
 Gives your app a dictionary of parameters to handle, following a launch from notification or campaign action, and allows you to receive interactive notification action.

 actionIdentifier, actionTitle and completionHandler are nil if the associated campaign or push notification is not an interactive push notification.

 @warning The completionHandler comes from the default interactive notification handling methods. Make sure you call it if it is not nil as it won't be called by FA if passed to you.
 
 @param customParameters Deep-linking parameters received from FollowAnalytics.
 @param actionIdentifier Comes from an interactive notification.
 @param actionTitle Comes from an interactive notification.
 @param completionHandler Comes from an interactive notification. Call it if it is not nil.
 */
- (void)followAppsShouldHandleParameters:(NSDictionary *_Nullable)customParameters
                        actionIdentifier:(NSString *_Nullable)actionIdentifier
                             actionTitle:(NSString *_Nullable)actionTitle
                       completionHandler:(void (^_Nullable)())completionHandler;

/*!
 Allows the user to handle themselves a rich campaign and its parameters.
 
 @param url the URL associated to the rich campaign.
 @param urlTitle title associated to the URL.
 @param params Rich campaign parameters. Could be used for deeplinkng, knowing how or where to show the URL, and so on.
 */
- (void)followAppsShouldHandleWebViewUrl:(NSURL *_Nullable)url
							   withTitle:(NSString *_Nullable)urlTitle
						customParameters:(NSDictionary *_Nullable)params;


/*!
 Allows the user to handle themselves a rich campaign and its parameters.
 
 This method is deprecated, please use `followAppsShouldHandleWebViewUrl:withTitle:customParameters:` instead.
 
 @deprecated
 */
- (void)followAppsShouldHandleWebViewUrl:(NSURL *_Nullable)url
                               withTitle:(NSString *_Nullable)webviewTitle __attribute__((deprecated));


/*!
 If you use category with notification, you should register them in this method.
 */
- (void)followAppsRegisterNotificationCategories;


/*!
 This delegate is called when there is an openUrl in the notification.
 If you implement it, you have to call the completionOpenUrl when your app is ready to execute the deepLinking.
 */
- (void)followAppsNotificationHandleOpenURLWithCompletion:(void (^_Nonnull)(void))completionOpenUrl;

@end


// _____________________________________________________
// --------------------- FAWebView ---------------------

/*!
 Use this web view if you want to be able to tag events and errors directly from Javascript (using FAWebView.js)
*/
@interface FAWebView : UIWebView
@end


// _____________________________________________________
// ----------------- Adaptive SDK keys -----------------

UIKIT_EXTERN NSString * _Nonnull const FASDKLocalyticsKey;
UIKIT_EXTERN NSString * _Nonnull const FASDKUrbanAirshipKey;
UIKIT_EXTERN NSString * _Nonnull const FASDKMixpanelKey;
UIKIT_EXTERN NSString * _Nonnull const FASDKGoogleAnalyticsKey;
UIKIT_EXTERN NSString * _Nonnull const FASDKTuneKey;
UIKIT_EXTERN NSString * _Nonnull const FASDKSegmentKey;
UIKIT_EXTERN NSString * _Nonnull const TUSessionId;
UIKIT_EXTERN NSString * _Nonnull const TUUserId;
