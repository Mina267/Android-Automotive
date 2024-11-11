# Android Data Storage and SQLite Database Integration

### 1. **Overview of Data Storage Options in Android**
Android provides several data storage options:
- **Shared Preferences**: Store primitive data in key-value pairs.
- **Internal Storage**: Store private data on the device.
- **External Storage**: Store public data on the external storage.
- **SQLite Database**: Store structured data in a private database.

### 2. **Working with Shared Preferences**
SharedPreferences allows saving key-value pairs of primitive data types, which persist across user sessions.

#### Saving Data
```java
SharedPreferences preferences = getPreferences(Context.MODE_PRIVATE);
SharedPreferences.Editor editor = preferences.edit();
editor.putString("PHONE_KEY", phoneNumber);
editor.putString("MESSAGE_KEY", message);
editor.commit();
```

#### Retrieving Data
```java
SharedPreferences preferences = getPreferences(Context.MODE_PRIVATE);
String phone = preferences.getString("PHONE_KEY", "N/A");
String message = preferences.getString("MESSAGE_KEY", "N/A");
```

### 3. **Internal Storage**
Internal Storage is private to the application. Data can be read and written using `FileInputStream` and `FileOutputStream`.

#### Writing to Internal Storage
```java
FileOutputStream fos = openFileOutput("APP_FILE", Context.MODE_PRIVATE);
DataOutputStream dos = new DataOutputStream(fos);
dos.writeUTF(phone);
dos.writeUTF(message);
dos.close();
```

#### Reading from Internal Storage
```java
FileInputStream fis = openFileInput("APP_FILE");
DataInputStream dis = new DataInputStream(fis);
String phone = dis.readUTF();
String message = dis.readUTF();
dis.close();
```

### 4. **SQLite Database**
SQLite is a relational database for structured data. You need a helper class extending `SQLiteOpenHelper` for database management.

#### Helper Class
```java
class DatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "MESSAGE_PHONE_LOG.db";
    private static final int DATABASE_VERSION = 1;
    private static final String TABLE_NAME = "MESSAGE_PHONE_LOG";
    private static final String COL_UID = "_id";
    private static final String COL_PHONE = "phone";
    private static final String COL_MESSAGE = "message";
    
    private static final String CREATE_TABLE = "CREATE TABLE " + TABLE_NAME + " (" + COL_UID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + COL_PHONE + " TEXT, " + COL_MESSAGE + " TEXT);";

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Handle database upgrades
    }
}
```

#### Database Adapter Class
This class abstracts database operations like insert, query, etc.

```java
public class DatabaseAdapter {
    private DatabaseHelper dbHelper;

    public DatabaseAdapter(Context context) {
        dbHelper = new DatabaseHelper(context);
    }

    // Insert phone and message into the database
    public long insertPhoneMessage(MyAppDTO entry) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put("phone", entry.getPhone());
        values.put("message", entry.getMessage());
        return db.insert("MESSAGE_PHONE_LOG", null, values);
    }

    // Retrieve message by phone number
    public MyAppDTO getMessage(String phone) {
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        Cursor cursor = db.query("MESSAGE_PHONE_LOG", new String[]{"phone", "message"}, "phone=?", new String[]{phone}, null, null, null);
        
        MyAppDTO entry = null;
        if (cursor.moveToNext()) {
            entry = new MyAppDTO(cursor.getString(0), cursor.getString(1));
        }
        cursor.close();
        return entry;
    }
}
```

### 5. **DTO Class**
This Data Transfer Object (DTO) holds the phone number and message data.
```java
public class MyAppDTO {
    private String phone;
    private String message;

    public MyAppDTO(String phone, String message) {
        this.phone = phone;
        this.message = message;
    }

    public String getPhone() {
        return phone;
    }

    public String getMessage() {
        return message;
    }
}
```

### 6. **Main Activity Integration**
In `ActivityTwo`, integrate all storage options (SharedPreferences, Internal Storage, and SQLite) for saving and retrieving data.

#### Writing Data to SQLite
```java
DatabaseAdapter adapter = new DatabaseAdapter(this);
adapter.insertPhoneMessage(new MyAppDTO(txtPhone.getText().toString(), txtMessage.getText().toString()));
```

#### Reading Data from SQLite
```java
MyAppDTO dataResult = adapter.getMessage(txtPhone.getText().toString());
txtMessage.setText(dataResult.getMessage());
```

### 7. **Summary of File I/O and Streams**
- **FileInputStream**: Reads raw byte data from a file.
- **FileOutputStream**: Writes raw byte data to a file.
- **DataInputStream**: Reads primitive data types (e.g., int, float, String) from an input stream.
- **DataOutputStream**: Writes primitive data types to an output stream.

#### Example for Writing Data to File Using Streams
```java
FileOutputStream fos = openFileOutput("data_file", Context.MODE_PRIVATE);
DataOutputStream dos = new DataOutputStream(fos);
dos.writeUTF("Hello, World!");
dos.close();
```

#### Example for Reading Data from File Using Streams
```java
FileInputStream fis = openFileInput("data_file");
DataInputStream dis = new DataInputStream(fis);
String data = dis.readUTF();
dis.close();
```

---

### 8. **SQLite Queries and Cursor Management**
- **Insert**: Use `ContentValues` to prepare data and insert it into the database.
- **Retrieve**: Use `Cursor` to handle database query results, which act as pointers to data.

**Cursor Example:**
```java
Cursor cursor = db.query("TABLE_NAME", new String[]{"COLUMN1", "COLUMN2"}, "COLUMN1 = ?", new String[]{value}, null, null, null);
```

### 9. **Best Practices**
- Use **SharedPreferences** for small, key-value pair data.
- Use **Internal Storage** for larger, private data files.
- Use **SQLite** for structured data that needs querying and complex relationships.

