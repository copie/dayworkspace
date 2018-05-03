# Flask_wtf_FieldList_使用总结

Flask 的其他文档挺多的,我在用 Flask 遇到问题的时候文档都可以明确的找到,但是唯独我用 FiledList 的时候文档写的很模糊, 没有说明我要具体怎么用, 文档只说了如何定义.
要想用到自己的项目中的话,他们之间还是有一点差距的, 从网上查的东西也是零零碎碎的.没有办法通过自己摸索解决了这个问题.

## 问题说明

使用 Flask-wtf 写表单的时候,我们的需求是接受不定数量的字段的提交.具体就是我要显示 n 条信息(比如:标签) 然后用户通过自己的选择其中 m( m<=n ) 条,进行删除操作,我需要建立一个表单来完成这个操作.ps:网上有些例子只是服务段接受数据, 

## 具体实现

就是使用 FieldList 来实现,

简单定义

```python
    class IDListForm(FlaskForm):
        id_list = FieldList(IntegerField('ID号'))
        submit = SubmitField('提交')
```

稍微复杂的定义

```python
class TimeForm(FlaskForm):
    opening = StringField('Opening Hour')
    closing = StringField('Closing Hour')
    day = HiddenField('Day')

class BusinessForm(FlaskForm):
    name = StringField('Business Name')
    hours = FieldList(FormField(TimeForm), min_entries=7, max_entries=7)
```

这里限定了最多和最少的项目数(但是我们的需求是不确定用户会有多少的提交.)
这里这个例子只是说明可以这么用.(简单例子就可以解决我们的问题)

```python
[manage/view.py]
@manage.route('/manage/posts', methods=['GET', 'POST'])
def manage_posts():
    posts = Post.query.all()
    id_list = IDListForm()
    if id_list.validate_on_submit():
        print(id_list.id_list.data)
    return render_template('manage/posts.html', posts=posts,id_list=id_list)
```

从这个 view 可以看出我们要将数据库中所有的文章都查询出来,然后通过 manage/posts.html 模板显示出来.

```html
<form action="" method="post">
{{ id_list.hidden_tag() }}
{% for post in posts %}
<tr>
    <td><input type="checkbox" name="id_list-{{ loop.index0 }}" id="id_list-{{ loop.index0 }}" value="{{ post.id }}"></td>
    <td>{{ loop.index }}</td>
    <td>{{ post.id }}</td>
    <td>{{ post.title }}</td>
    <td>{{ post.author.username }}</td>
    <td>{{ post.tags.all()|join(',', attribute='tag') }}</td>
    <td>{{ post.classifys.all()|join(',', attribute='classify') }}</td>
    <td>{{ post.timestamp}}</td>
    <td><a href="{{ url_for('manage.manageblog',id=post.id,next=url_for('manage.manage_posts')) }}">修改</a></td>
</tr>
    {% endfor %}
    {{ id_list.submit() }}    
</form>
```

这个就是我们的表单的书写 我们看到我们提交的时候只会提交 checkbox 的 value ,而 value 是等于 post.id, 后端接受到 Post 的信息就是用户要操作的那一组文章了, 注意 name 和 id 为 (form 定义的字段名-[0,1,2,3,...]) 这个规律.比如(id_list-{{ loop.index0 }})