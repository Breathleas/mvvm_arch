package com.god.seep.mvvm;

import com.god.seep.base.adapter.BaseRecyclerViewAdapter;
import com.god.seep.base.arch.view.BaseActivity;
import com.god.seep.base.arch.viewmodel.BaseViewModel;
import com.god.seep.mvvm.databinding.ActivityMainBinding;
import com.god.seep.mvvm.databinding.ItemChapterBinding;

import android.view.Menu;
import android.view.MenuItem;

import java.util.List;

import androidx.lifecycle.Observer;

public class MainActivity extends BaseActivity<ActivityMainBinding, BaseViewModel> {

    @Override
    public int getLayoutId() {
        return R.layout.activity_main;
    }

    @Override
    public BaseViewModel createViewModel() {
        return new MainViewModel(this.getApplication(), new MainModel());
    }

    BaseRecyclerViewAdapter adapter = new BaseRecyclerViewAdapter<ItemChapterBinding, Chapter>(R.layout.item_chapter) {
        @Override
        protected void bindItem(ItemChapterBinding binding, Chapter item) {
            binding.setChapter(item);
        }
    };

    @Override
    public void initData() {
        mBinding.setViewModel((MainViewModel) mViewModel);
        setSupportActionBar(mBinding.toolbar);
        mBinding.list.setAdapter(adapter);
        ((MainViewModel) mViewModel).getChapterListEvent().observe(this, new Observer<List<Chapter>>() {
            @Override
            public void onChanged(List<Chapter> chapters) {
                adapter.addData(chapters);
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
