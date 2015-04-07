#ifndef __COMMON_H__
#define __COMMON_H__

#include <tuple>
#include <string>
#include <vector>
#include <openrave-core.h>
#include <boost/typeof/std/string.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/map.hpp>
#include <boost/typeof/std/set.hpp>
#include <boost/typeof/std/string.hpp>

#define FOREACH(it, v) for(BOOST_TYPEOF(v) ::iterator it = (v).begin(), __itend__=(v).end(); it != __itend__; ++(it))
#define FOREACHC(it, v) for(BOOST_TYPEOF(v) ::const_iterator it = (v).begin(), __itend__=(v).end(); it != __itend__; ++(it))

#include <zmq.hpp>
#include <zhelpers.hpp>

typedef boost::shared_ptr<zmq::context_t> ZmqContextPtr;
typedef boost::shared_ptr<zmq::socket_t> ZmqSocketPtr;
typedef boost::shared_ptr<zmq::message_t> ZmqMessagePtr;

#endif