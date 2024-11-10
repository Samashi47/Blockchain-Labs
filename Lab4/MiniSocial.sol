// SPDX-License-Identifier: GPL-3.0

pragma solidity ^0.8.0;

contract MiniSocial {
    // Define the structure of a post
    struct Post {
        uint id;
        address author;
        string tweet;
        int votes;
        string[] comments;
        uint timestamp;
    }
    
    Post[] public posts;
    mapping(uint => mapping(address => bool)) public hasUpvoted;
    mapping(uint => mapping(address => bool)) public hasDownvoted;

    constructor() {
        publishPost("I hereby declare, This is the first post!");
    }

    modifier isAuthor(uint index) {
        require(msg.sender == posts[index].author, "Nice Try!! But you are not the author of this post!");
        _;
    }

    function publishPost(string memory _message) public {
        posts.push(Post(posts.length, msg.sender, _message, 0, new string[](0), block.timestamp));
    }

    function getPost(uint index) public view returns (uint, string memory, address, uint){
        return (posts[index].id , posts[index].tweet, posts[index].author, posts[index].timestamp);
    }

    function getTotalPosts() public view returns (uint) {
        return posts.length;
    }

    function upvotePost(uint index) public {
        require(!hasUpvoted[index][msg.sender], "You really like this post, don't you? But NO");
        posts[index].votes++;
        hasUpvoted[index][msg.sender] = true;
        hasDownvoted[index][msg.sender] = false;
    }

    function downvotePost(uint index) public {
        require(!hasDownvoted[index][msg.sender], "You can't hate the same post twice!");
        posts[index].votes--;
        hasDownvoted[index][msg.sender] = true;
        hasUpvoted[index][msg.sender] = false;
    }

    function getPostVotes(uint index) public view returns (int) {
        return posts[index].votes;
    }

    function modPost(uint index, string memory _message) public isAuthor(index) {
        posts[index].tweet = _message;
    }

    function deletePost(uint index) public isAuthor(index) {
        delete posts[index];
    }

    function commentOnPost(uint index, string memory _comment) public {
        posts[index].comments.push(_comment);
    }

    function getPostComments(uint index) public view returns (string[] memory) {
        return posts[index].comments;
    }
}