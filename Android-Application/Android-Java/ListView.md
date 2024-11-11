# ListView Example Application

## Introduction

This project demonstrates how to implement a custom `ListView` in Android using an adapter to manage and display a list of custom objects (`MyItem`). It efficiently binds data to views through a `ViewHolder`, ensuring smooth scrolling and performance.

## Code Overview

### 1. MyItem Class

The `MyItem` class models the data that will be displayed in each row of the `ListView`. It includes three fields 
- itemName the title of the item.
- itemDescription the item's description.
- itemIcon a reference to an icon image (integer resource).

#### Example Code
```java
public class MyItem {
    private String itemName;
    private String itemDescription;
    private int itemIcon;

    public MyItem(String itemName, String itemDescription, int itemIcon) {
        this.itemName = itemName;
        this.itemDescription = itemDescription;
        this.itemIcon = itemIcon;
    }

    public String getItemName() { return itemName; }
    public void setItemName(String itemName) { this.itemName = itemName; }

    public String getItemDescription() { return itemDescription; }
    public void setItemDescription(String itemDescription) { this.itemDescription = itemDescription; }

    public int getItemIcon() { return itemIcon; }
    public void setItemIcon(int itemIcon) { this.itemIcon = itemIcon; }

    @Override
    public String toString() { return getItemName(); }
}
```
### 2. ViewHolder Class

The `ViewHolder` class is used to improve the performance of the `ListView`. Instead of calling `findViewById()` every time a row is drawn, it caches the views for each row. This avoids unnecessary calls and improves the scrolling experience.

#### Key Concept
- convertView The view object representing each row.
- getters for `TextView` and `ImageView` ensure views are only initialized when needed (lazy initialization).

#### Example Code
```java
public class ViewHolder {
    View convertView;
    TextView txtTitle;
    TextView txtDescription;
    ImageView imgView;

    public ViewHolder(View convertView) {
        this.convertView = convertView;
    }

    public TextView getTxtTitle() {
        if (txtTitle == null) {
            txtTitle = convertView.findViewById(R.id.txtTitle);
        }
        return txtTitle;
    }

    public TextView getTxtDescription() {
        if (txtDescription == null) {
            txtDescription = convertView.findViewById(R.id.txtDescription);
        }
        return txtDescription;
    }

    public ImageView getImgView() {
        if (imgView == null) {
            imgView = convertView.findViewById(R.id.imgView);
        }
        return imgView;
    }
}
```

### 3. ItemArrayAdapter Class

The `ItemArrayAdapter` extends `ArrayAdapter` and is responsible for binding the data from the `MyItem` class to the `ListView`. The adapter uses the `ViewHolder` to optimize performance.

#### Key Concepts
- getView() This method populates each row of the `ListView` by recycling views and setting data to the respective view elements (title, description, icon).
- Row Recycling Reuses existing row views to avoid inflating new layouts unnecessarily.

#### Example Code
```java
public class ItemArrayAdapter extends ArrayAdapter {
    private VectorMyItem myItems;
    private Context _context;

    public ItemArrayAdapter(Context context, int resource, int textViewResourceId, List items) {
        super(context, resource, textViewResourceId, items);
        myItems = (VectorMyItem) items;
        _context = context;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup listView) {
        View row = convertView;
        ViewHolder viewHolder;

        if (row == null) {
            LayoutInflater inflater = (LayoutInflater) _context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            row = inflater.inflate(R.layout.row, listView, false);
            viewHolder = new ViewHolder(row);
            row.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder) row.getTag();
        }

         Bind data to the views
        viewHolder.getImgView().setImageResource(myItems.get(position).getItemIcon());
        viewHolder.getTxtTitle().setText(myItems.get(position).getItemName());
        viewHolder.getTxtDescription().setText(myItems.get(position).getItemDescription());

        return row;
    }
}
```

### 4. MainActivity Class

The `MainActivity` is responsible for initializing the list and setting the adapter. It creates a list of `MyItem` objects and attaches them to the `ListView` using the `ItemArrayAdapter`.

#### Key Concepts
- ListView setup The `ItemArrayAdapter` is set as the adapter for the `ListView`, which automatically binds the data to the view.
- OnItemClickListener Handles item clicks and displays a toast message containing the name of the clicked item.

#### Example Code
```java
public class MainActivity extends AppCompatActivity {
    private ItemArrayAdapter adapter;
    private ListView lstItems;
    private VectorMyItem items;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

         Create and populate the list of items
        items = new Vector();
        items.add(new MyItem(Item Zero, Item Zero Desc!, R.mipmap.zero));
        items.add(new MyItem(Item One, Item Zero One!, R.mipmap.one));

         Set up the ListView and adapter
        lstItems = findViewById(R.id.lstProducts);
        adapter = new ItemArrayAdapter(this, R.layout.row, R.id.txtTitle, items);
        lstItems.setAdapter(adapter);

         Set up an item click listener
        lstItems.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView parent, View view, int position, long id) {
                Toast.makeText(MainActivity.this, parent.getAdapter().getItem(position).toString(), Toast.LENGTH_SHORT).show();
            }
        });
    }
}
```

