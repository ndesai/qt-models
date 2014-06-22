# Qt Models
### A collection of custom models



- SQLiteDatabase
 
```
Models.SQLiteDatabase {
    id: root
    source: "sample.db"
    
    function getPhotos() 
    {
            executeQuery("SELECT * FROM photos", function(query, status, result) 			{
            if(status)
            {
				// result is an array
				// can be fed directly into a Qt Quick View
				// data can be referenced using modelData.propertyName
            }
        });
    }
}
```

- Creates database if doesn't exist
- Database path uses StandardLocation

- iOS

```
QStandardPaths::standardLocations(QStandardPaths::DataLocation).first()
```

- OSX

```
QString(QDir::homePath() + QDir::separator())
```

## TODO

- Threaded SQL access
- Android support
- Increased model support
