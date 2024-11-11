

### 1. **Using Interface for Communication (MainActivity as a Communicator)**

In this method, an interface is used to facilitate communication between two fragments via the parent activity (`MainActivity`).

#### Logic:
- The `StaticFragment` sends data (e.g., a counter) to the `MainActivity` via an interface.
- The `MainActivity` implements the interface and passes the data to the `DynamicFragment`.

#### Code Illustration:

**Interface:**
```java
public interface Communicator {
    void count(int cnt);
}
```

**StaticFragment:**
```java
public class StaticFragment extends Fragment {
    private Communicator comm;
    private int cnt = 0;

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        comm = (Communicator) getActivity();
        Button btnCount = view.findViewById(R.id.StaticFragbtn);
        btnCount.setOnClickListener(v -> {
            cnt++;
            comm.count(cnt); // Sending data to MainActivity
        });
    }
}
```

**MainActivity (Implements Communicator):**
```java
public class MainActivity extends AppCompatActivity implements Communicator {
    private DynamicFragment dynamicFragment;

    @Override
    public void count(int cnt) {
        dynamicFragment.changeCnt(cnt); // Passing data to DynamicFragment
    }
}
```

**DynamicFragment:**
```java
public class DynamicFragment extends Fragment {
    private TextView dynamicTxtView;

    public void changeCnt(int cnt) {
        dynamicTxtView.setText(String.valueOf(cnt)); // Updating UI
    }
}
```

---

### 2. **Using SharedViewModel (ViewModel for Communication)**

This method uses a `SharedViewModel` to share data between fragments without involving the activity directly.

#### Logic:
- Both `StaticFragment` and `DynamicFragment` observe and share data using a shared `ViewModel`.
- The `ViewModel` holds the data, and both fragments can read from and write to it.

#### Code Illustration:

**SharedViewModel:**
```java
public class SharedViewModel extends ViewModel {
    private MutableLiveData<Integer> counter = new MutableLiveData<>();

    public LiveData<Integer> getData() {
        return counter;
    }

    public void setData(int cnt) {
        counter.setValue(cnt); // Updating counter in ViewModel
    }
}
```

**StaticFragment:**
```java
public class StaticFragment extends Fragment {
    private SharedViewModel sharedViewModel;
    private int cnt = 0;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_static, container, false);
        sharedViewModel = new ViewModelProvider(requireActivity()).get(SharedViewModel.class);

        Button btnCount = view.findViewById(R.id.StaticFragbtn);
        btnCount.setOnClickListener(v -> {
            cnt++;
            sharedViewModel.setData(cnt); // Sending data to ViewModel
        });
        return view;
    }
}
```

**DynamicFragment:**
```java
public class DynamicFragment extends Fragment {
    private SharedViewModel sharedViewModel;
    private TextView dynamicTxtView;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_dynamic, container, false);
        sharedViewModel = new ViewModelProvider(requireActivity()).get(SharedViewModel.class);

        sharedViewModel.getData().observe(getViewLifecycleOwner(), cnt -> {
            dynamicTxtView.setText(String.valueOf(cnt)); // Updating UI with data from ViewModel
        });

        return view;
    }
}
```

---

### 3. **Using FragmentResult API**

This method uses the `FragmentResult` API to pass data between fragments.

#### Logic:
- `StaticFragment` sends data as a `Bundle` using `setFragmentResult`.
- `DynamicFragment` listens for results using `setFragmentResultListener`.

#### Code Illustration:

**StaticFragment:**
```java
public class StaticFragment extends Fragment {
    private int cnt = 0;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_static, container, false);
        Button btnCount = view.findViewById(R.id.StaticFragbtn);
        btnCount.setOnClickListener(v -> {
            cnt++;
            Bundle result = new Bundle();
            result.putInt("cnt", cnt);
            getParentFragmentManager().setFragmentResult("countKey", result); // Sending data
        });
        return view;
    }
}
```

**DynamicFragment:**
```java
public class DynamicFragment extends Fragment {
    private TextView dynamicTxtView;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_dynamic, container, false);
        dynamicTxtView = view.findViewById(R.id.DynamicTxtVeiw);

        getParentFragmentManager().setFragmentResultListener("countKey", this, (key, bundle) -> {
            int cnt = bundle.getInt("cnt");
            dynamicTxtView.setText(String.valueOf(cnt)); // Updating UI with result
        });

        return view;
    }
}
```

---

### Summary:

1. **Interface Communication:** Use an interface to communicate between fragments through the parent activity.
2. **SharedViewModel:** Share data between fragments using `ViewModel` for direct data sharing without involving the activity.
3. **FragmentResult API:** Send data between fragments using `setFragmentResult` and `setFragmentResultListener`.

