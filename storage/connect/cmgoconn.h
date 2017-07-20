/***********************************************************************/
/*  CMgoConn.h : header file for the MongoDB connection classes.       */
/***********************************************************************/

/***********************************************************************/
/*  Include MongoDB library header files.                       	  	 */
/***********************************************************************/
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

// C connection to a MongoDB data source
class TDBMGO;
class MGOCOL;

/***********************************************************************/
/*  Include MongoDB library header files.                       	  	 */
/***********************************************************************/
typedef class INCOL  *PINCOL;
typedef class MGODEF *PMGODEF;
typedef class TDBMGO *PTDBMGO;
typedef class MGOCOL *PMGOCOL;

typedef struct mongo_parms {
	PTDB Tdbp;
	PCSZ Uristr;               // Driver URI
	PCSZ Db_name;
	PCSZ Coll_name;
	PCSZ Options;
	PCSZ Filter;
	bool Pipe;
//PCSZ User;                 // User connect info
//PCSZ Pwd;                  // Password connect info
//int  Fsize;								 // Fetch size
//bool Scrollable;					 // Scrollable cursor
} CMGOPARM, *PCPARM;

typedef struct KEYCOL {
	KEYCOL *Next;
	PINCOL  Incolp;
	PCOL    Colp;
	char   *Key;
} *PKC;

/***********************************************************************/
/*  Used when inserting values in a MongoDB collection.                */
/***********************************************************************/
class INCOL : public BLOCK {
public:
	// Constructor
	INCOL(bool ar) { Klist = NULL; Array = ar; }

	// Methods
	void AddCol(PGLOBAL g, PCOL colp, char *jp);

	//Members
	bson_t Child;
	PKC    Klist;
	bool   Array;
}; // end of INCOL;

/***********************************************************************/
/*  CMgoConn class.                                                   */
/***********************************************************************/
class CMgoConn : public BLOCK {
	friend class TDBMGO;
	friend class MGODISC;
public:
	// Constructor
	CMgoConn(PGLOBAL g, PCPARM pcg);

	//static void *mgo_alloc(size_t n);
	//static void *mgo_calloc(size_t n, size_t sz);
	//static void *mgo_realloc(void *m, size_t n);
	//static void  mgo_free(void *) {}

	// Implementation
	bool IsConnected(void) { return m_Connected; }
	bool Connect(PGLOBAL g);
	int  CollSize(PGLOBAL g);
	bool MakeCursor(PGLOBAL g);
	int  ReadNext(PGLOBAL g);
	PSZ  GetDocument(PGLOBAL g);
	void ShowDocument(bson_iter_t *iter, const bson_t *doc, const char *k);
	void MakeColumnGroups(PGLOBAL g);
	bool DocWrite(PGLOBAL g, PINCOL icp);
	int  Write(PGLOBAL g);
	bool DocDelete(PGLOBAL g);
	void Rewind(void);
	void Close(void);
	PSZ  Mini(PGLOBAL g, PCOL colp, const bson_t *bson, bool b);
	void GetColumnValue(PGLOBAL g, PCOL colp);
	bool AddValue(PGLOBAL g, PCOL colp, bson_t *doc, char *key, bool upd);

protected:
	// Members
	PCPARM								Pcg;
	mongoc_uri_t         *Uri;
	mongoc_client_pool_t *Pool;				// Thread safe client pool
	mongoc_client_t      *Client;		  // The MongoDB client
	mongoc_database_t    *Database;	  // The MongoDB database
	mongoc_collection_t  *Collection; // The MongoDB collection
	mongoc_cursor_t      *Cursor;
	const bson_t         *Document;
	bson_t               *Query;			// MongoDB cursor filter
	bson_t               *Opts;			  // MongoDB cursor options
	bson_error_t          Error;
	bson_iter_t           Iter;				// Used to retrieve column value
	bson_iter_t           Desc;				// Descendant iter
	PINCOL                Fpc;				// To insert INCOL classes
	bool                  m_Connected;
}; // end of class CMgoConn
