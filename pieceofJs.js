/* FRONTEND */

const deleteComment = (postId,id)=>{
    console.log(id);
    fetch("/deletecomment",{
      method: "put",
      headers:{
        "Content-Type": "application/json",
        "Authorization": "Bearer " + localStorage.getItem("token")
      },
      body: JSON.stringify({
        commentId: id,
        postId
      })
    }).then(res=>res.json()).then(result => {
      console.log(result);
      const newData = data.map(item =>{
        if(item._id === result._id){
          return result;
        }else{
          return item;
        }
      })
      setData(newData);
    })
  }

  /* BACKEND */
  router.put("/comment",requireLogin, (req,res) =>{
    const comment = {
        text: req.body.text,
        postedBy: req.user._id
    }
    Posts.findByIdAndUpdate(req.body.postId,{
        $push:{
            comments: comment
        }
    }, {
        new: true
    }).populate("comments.postedBy", "_id name").populate("postedBy", "_id name").exec((err,result) =>
    {
        if(err){
            return res.status(422).json({error: err})
        }else{
            res.json(result);
        }
    })
});