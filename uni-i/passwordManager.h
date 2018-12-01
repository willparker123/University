/* passwordmanager library module. */
typedef struct
{
  char *username;
  char *password;
} cred;

//structure for a login for one website, with 'site' being an index
typedef struct
{
  char *site;
  cred *cred;
} user;
//struct for an array of users
typedef struct
{
  user *content;
  size_t length;
  size_t size;
} arrayUsers;
//structure for a master login, with a pointer to their stored accounts
typedef struct
{
  cred *cred;
  arrayUsers *users;
} muser;
//struct for an array of musers
typedef struct
{
  muser *content;
  size_t length;
  size_t size;
} arrayMUsers;

void reqCredMUser(arrayMUsers *musers, bool hasAccount);

void reqLoginMUser(arrayMUsers *musers);

void reqOptions(arrayMUsers *musers);

void options(arrayMUsers *musers);
